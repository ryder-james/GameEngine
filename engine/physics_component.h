#pragma once
#include "component.h"

class PhysicsComponent : public Component {
public:
	enum ForceType {
		kForce,
		kVelocity,
		kImpulse
	};

public:
	PhysicsComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	PhysicsComponent* Clone() override { return new PhysicsComponent(*this); }

	void Update() override;

	void AddForce(const vector2& force, ForceType type);
	void AddTorque(float torque, ForceType type);

	vector2 GetVelocity() { return velocity_; }

protected:
	float drag_ = 0.0f;
	float torque_ = 0.0f;
	float max_velocity_ = 0.0f;
	float max_angular_velocity_ = 0.0f;

	float angular_drag_ = 0.0f;
	float angular_velocity_ = 0.0f;

	vector2 force_ = vector2::zero;
	vector2 velocity_ = vector2::zero;

	ForceType force_type_;
};
