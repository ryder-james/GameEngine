#include "physics_component.h"

#include "..\\core\timer.h"

void PhysicsComponent::Destroy() {}

bool PhysicsComponent::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "drag", drag_);
	success = json::get(value, "angular_drag", angular_drag_);
	success = json::get(value, "max_velocity", max_velocity_);
	success = json::get(value, "max_angular_velocity", max_angular_velocity_);

	return success;
}

void PhysicsComponent::Update() {
	velocity_ += (force_ * g_timer.dt);
	if (velocity_.length() > max_velocity_) {
		velocity_ = velocity_.normalized() * max_velocity_;
	}
	owner_->GetTransform().translation += (velocity_ * g_timer.dt);
	velocity_ *= pow(drag_, g_timer.dt);
	if (force_type_ == kImpulse) force_ = vector2::zero;

	angular_velocity_ += (torque_ * g_timer.dt);
	angular_velocity_ = math::clamp(angular_velocity_, -max_angular_velocity_, max_angular_velocity_);
	owner_->GetTransform().rotation += (angular_velocity_ * g_timer.dt);
	angular_velocity_ *= pow(angular_drag_, g_timer.dt);
}

void PhysicsComponent::AddForce(const vector2& force, ForceType type) {
	force_type_ = type;
	switch (force_type_) {
	case PhysicsComponent::kForce:
	case PhysicsComponent::kImpulse:
		force_ = force;
		break;
	case PhysicsComponent::kVelocity:
		velocity_ = force;
		force_ = vector2::zero;
		break;
	}
}

void PhysicsComponent::AddTorque(float torque, ForceType type) {
	switch (force_type_) {
	case PhysicsComponent::kImpulse:
	case PhysicsComponent::kForce:
		torque_ = torque;
		break;
	case PhysicsComponent::kVelocity:
		angular_velocity_ = torque;
		torque_ = 0.0f;
		break;
	}

}
