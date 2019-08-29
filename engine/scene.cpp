#include "scene.h"

#include "entity.h"
#include "sprite_component.h"
#include "sprite_animation_component.h"
#include "text_component.h"
#include "audio_component.h"
#include "controller_component.h"
#include "physics_component.h"
#include "moving_component.h"
#include "weapon_component.h"
#include "player_component.h"
#include "circle_collision_component.h"
#include "time_component.h"
#include "emitter_component.h"

#include "..\\core\random.h"

bool Scene::Create(const Name& name, Engine* engine) {
	name_ = name;
	engine_ = engine;

	object_factory_ = new ObjectFactory();
	object_factory_->Register("entity", new Creator<Entity, Object>());
	object_factory_->Register("sprite_component", new Creator<SpriteComponent, Object>());
	object_factory_->Register("sprite_animation_component", new Creator<SpriteAnimationComponent, Object>());
	object_factory_->Register("text_component", new Creator<TextComponent, Object>());
	object_factory_->Register("audio_component", new Creator<AudioComponent, Object>());
	object_factory_->Register("controller_component", new Creator<ControllerComponent, Object>());
	object_factory_->Register("physics_component", new Creator<PhysicsComponent, Object>());
	object_factory_->Register("moving_component", new Creator<MovingComponent, Object>());
	object_factory_->Register("weapon_component", new Creator<WeaponComponent, Object>());
	object_factory_->Register("player_component", new Creator<PlayerComponent, Object>());
	object_factory_->Register("circle_collision_component", new Creator<CircleCollisionComponent, Object>());
	object_factory_->Register("time_component", new Creator<TimeComponent, Object>());
	object_factory_->Register("emitter_component", new Creator<EmitterComponent, Object>());

	return true;
}

void Scene::Destroy() {
	for (Entity* entity : entities_) {
		entity->Destroy();
		delete entity;
	}

	entities_.clear();

	delete object_factory_;
}

bool Scene::Load(const rapidjson::Value& value) {
	bool success = false;

	const rapidjson::Value& ent_val = value["entities"];

	if (ent_val.IsArray()) {
		success = LoadEntities(ent_val);
	}

	return success;
}

void Scene::Initialize() {

}

void Scene::Update() {
	for (Entity* entity : entities_) {

		if (entity->state_[Entity::kActive]) {
			entity->Update();

 			if (entity->GetTransform().translation.x < 0.0f) entity->GetTransform().translation.x = 800.0f;
			if (entity->GetTransform().translation.x > 800.0f) entity->GetTransform().translation.x = 0.0f;
			if (entity->GetTransform().translation.y < 0.0f) entity->GetTransform().translation.y = 600.0f;
			if (entity->GetTransform().translation.y > 800.0f) entity->GetTransform().translation.y = 0.0f;
		}
	}

	auto iter = entities_.begin();
	while (iter != entities_.end()) {
		if ((*iter)->state_[Entity::kDestroy]) {
			(*iter)->Destroy();
			delete *iter;
			iter = entities_.erase(iter);
		} else {
			iter++;
		}
	}

	std::vector<CollisionComponent*> collision_components;
	for (Entity* entity : entities_) {
		CollisionComponent* component = entity->GetComponent<CollisionComponent>();
		if (component) {
			collision_components.push_back(component);
		}
	}

	for (size_t i = 0; i < collision_components.size(); i++) {
		for (size_t j = i + 1; j < collision_components.size(); j++) {
			if (collision_components[i]->GetOwner()->state_[Entity::kDestroy] ||
				collision_components[j]->GetOwner()->state_[Entity::kDestroy]) {
				continue;
			}

			if (collision_components[i]->Intersects(collision_components[j])) {
				Event<Entity> event;
				event.name = "collision";
				event.sender = collision_components[i]->GetOwner();
				event.receiver = collision_components[j]->GetOwner();

				engine_->GetSystem<EntityEventDispatcher>()->Notify(event);
			}
		}
	}
}

void Scene::Draw() {
	std::vector<RenderComponent*> render_components;

	for (Entity* entity : entities_) {
		if (entity->state_[Entity::kVisible]) {
			RenderComponent* render_component = entity->GetComponent<RenderComponent>();
			if (render_component) render_components.push_back(render_component);
		}
	}

	std::sort(render_components.begin(), render_components.end(), RenderComponent::SortZ);
	for (RenderComponent* render_component : render_components) {
		render_component->Draw();
	}
}

void Scene::Add(Entity* entity) {
	ASSERT(entity);
	ASSERT(std::find(entities_.begin(), entities_.end(), entity) == entities_.end());

	entity->Initialize();
	entities_.push_back(entity);
}

std::list<Entity*>::iterator Scene::Remove(Entity* entity, bool destroy) {
	ASSERT(entity);

	auto next_iter = entities_.end();

	auto iter = std::find(entities_.begin(), entities_.end(), entity);
	if (iter != entities_.end()) {
		if (destroy) {
			(*iter)->Destroy();
			delete* iter;
		}

		next_iter = entities_.erase(iter);
	}

	return next_iter;
}

Entity* Scene::GetEntityWithName(const Name& name) {
	Entity* entity = nullptr;

	for (Entity* _entity : entities_) {
		if (_entity->GetName() == name) {
			entity = _entity;
			break;
		}
	}

	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const Name& tag) {
	std::vector<Entity*> entities;

	for (Entity* _entity : entities_) {
		if (_entity->GetTag() == tag) {
			entities.push_back(_entity);
		}
	}

	return entities;
}

bool Scene::LoadEntities(const rapidjson::Value& value) {
	bool success = true;

	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& entity_val = value[i];
		if (entity_val.IsObject()) {
			Entity* entity = object_factory_->Create<Entity>("entity");
			entity->SetScene(this);
			if (entity->Load(entity_val)) {
				if (entity->IsSpawner()) {
					object_factory_->Register(entity->GetName(), new Spawner<Object>(entity));
				} else {
					Add(entity);
				}
			} else {
				success = false;
				delete entity;
			}
		} else {
			success = false;
		}
	}

	return success;
}
