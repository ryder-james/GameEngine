#include "entity.h"

#include "scene.h"
#include "component.h"
#include "render_component.h"

Entity::Entity(const Entity& entity) {
	name_ = entity.name_;
	tag_ = entity.tag_;
	scene_ = entity.scene_;
	lifetime_ = entity.lifetime_;
	is_spawner_ = entity.is_spawner_;
	transform_ = entity.transform_;
	state_ = entity.state_;

	for (Component* component : entity.components_) {
		Component* clone_component = dynamic_cast<Component*>(component->Clone());
		AddComponent(clone_component);
	}
}

bool Entity::Create(const Name& name, Scene* scene) {
	name_ = name;
	scene_ = scene;

	return true;
}

void Entity::Destroy() {
	for (Entity* child : children_) {
		child->Destroy();
		delete child;
	}

	children_.clear();

	for (Component* component : components_) {
		component->Destroy();
		delete component;
	}

	components_.clear();
}

bool Entity::Load(const rapidjson::Value& value) {
	bool success = true;

	success = json::get(value, "name", name_);
	success = json::get(value, "spawner", is_spawner_);
	success = json::get(value, "tag", tag_);
	success = json::get(value, "lifetime", lifetime_);

	std::string string;
	json::get(value, "state", string);

	std::vector<std::string> tokens;
	tokenize(string, '|', tokens);

	for (std::string& token : tokens) {
		token = "k" + token;
	}

	property_t<State> properties[] = {
		REFLECT_FORM(kActive),
		REFLECT_FORM(kVisible),
		REFLECT_FORM(kDestroy),
		REFLECT_FORM(kTransient)
	};

	state_ |= CreateBitMask<property_t<State>>(properties,
		sizeof(properties) / sizeof(property_t<State>),
		tokens);

	if (lifetime_ > 0) {
		state_.set(kTransient);
	}

	const rapidjson::Value& transform_value = value["transform"];
	if (transform_value.IsObject()) {
		transform_.Load(transform_value);
	} else {
		success = false;
	}

	const rapidjson::Value& components_value = value["components"];
	if (components_value.IsArray()) {
		success = LoadComponents(components_value);
	} else {
		success = false;
	}

	return success;
}

void Entity::Initialize() {
	for (Component* component : components_) {
		component->Initialize();
	}
}

void Entity::Update() {
	if (state_[kTransient]) {
		lifetime_ -= g_timer.dt;
		if (lifetime_ <= 0) {
			state_.set(kDestroy);
		}
	}

	for (Component* component : components_) {
		component->Update();
	}

	transform_.Update();
	if (parent_) {
		transform_.Update(parent_->transform_, local_transform_);
	}

	for (Entity* child : children_) {
		child->Update();
	}
}

void Entity::Draw() {
	transform_.Update();
	RenderComponent* component = GetComponent<RenderComponent>();
	if (component) {
		component->Draw();
	}
}

void Entity::AddComponent(Component* component) {
	ASSERT(component);
	ASSERT(std::find(components_.begin(), components_.end(), component) == components_.end());

	component->SetOwner(this);
	components_.push_back(component);
}

void Entity::RemoveComponent(Component* component) {
	ASSERT(component);

	auto iter = std::find(components_.begin(), components_.end(), component);
	if (iter != components_.end()) {
		(*iter)->Destroy();
		delete *iter;
		components_.erase(iter);
	}
}

void Entity::AddChild(Entity* child) {
	ASSERT(child);
	ASSERT(child->parent_ == nullptr);
	ASSERT(std::find(children_.begin(), children_.end(), child) == children_.end());

	child->parent_ = this;
	children_.push_back(child);
}

bool Entity::LoadComponents(const rapidjson::Value& value) {
	bool success = false;

	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& component_val = value[i];
		if (component_val.IsObject()) {
			Name type;
			json::get(component_val, "type", type);
			Component* component = scene_->GetObjectFactory()->Create<Component>(type);
			if (component && component->Load(component_val)) {
				success = true;
				AddComponent(component);
			}
		}
	}

	return success;
}
