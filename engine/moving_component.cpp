#include "moving_component.h"

#include "physics_component.h"
#include "sprite_animation_component.h"
#include "text_component.h"

#include "engine.h"
#include "scene.h"

void MovingComponent::Destroy() {
	owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Unsubscribe("collision", collision_event_handle_);
}

bool MovingComponent::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "score", score_);
	success = json::get(value, "force_range", force_range_);
	success = json::get(value, "torque_range", torque_range_);

	return success;
}

void MovingComponent::Initialize() {
	float force = g_random(force_range_[0], force_range_[1]);
	force_ = vector2::rotate(vector2(0.0f, force), g_random(0.0f, math::TWO_PI));

	torque_ = g_random(torque_range_[0], torque_range_[1]);

	PhysicsComponent* component = owner_->GetComponent<PhysicsComponent>();

	if (component) {
		component->AddForce(force_, PhysicsComponent::kVelocity);
		vector2 velocity = vector2::one;
		velocity = component->GetVelocity();
		owner_->GetTransform().rotation = vector2::get_angle(velocity) + math::HALF_PI;
	}

	collision_event_handle_ = owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()
		->Subscribe("collision", std::bind(&MovingComponent::OnCollision, this, std::placeholders::_1));
}

void MovingComponent::Update() {}

bool MovingComponent::OnCollision(const Event<Entity>& event) {
	if (event.sender == owner_ && event.receiver->GetTag() == "projectile") {
		owner_->state_.set(Entity::kDestroy);

		Event<Entity> event;
		event.name = "score";
		event.data[0].type = Variant::kInt;
		event.data[0].as_int = score_;
		owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Notify(event);

		if (owner_->GetName() == "red_ant") {
			Entity* dead_ant = owner_->GetScene()->GetObjectFactory()->Create<Entity>("dead_red_ant");
			dead_ant->GetTransform().translation = vector2(owner_->GetTransform().translation.x, owner_->GetTransform().translation.y);
			dead_ant->GetTransform().rotation = owner_->GetTransform().rotation;
			owner_->GetScene()->Add(dead_ant);

			Entity* black_ant = owner_->GetScene()->GetObjectFactory()->Create<Entity>("black_ant");
			black_ant->GetTransform().translation = vector2(owner_->GetTransform().translation.x, owner_->GetTransform().translation.y);
			owner_->GetScene()->Add(black_ant);
		} else {
			Entity* dead_ant = owner_->GetScene()->GetObjectFactory()->Create<Entity>("dead_black_ant");
			dead_ant->GetTransform().translation = vector2(owner_->GetTransform().translation.x, owner_->GetTransform().translation.y);
			dead_ant->GetTransform().rotation = owner_->GetTransform().rotation;
			owner_->GetScene()->Add(dead_ant);
		}
	}

	if (event.sender == owner_ && event.receiver->GetTag() == "food") {
		event.receiver->state_.set(Entity::kDestroy);

		Event<Entity> event;
		event.name = "food_devoured";
		owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Notify(event);
	}

	return true;
}
