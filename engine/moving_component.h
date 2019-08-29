#pragma once

#include "component.h"

#include "..\\core\core.h"

class MovingComponent : public Component {
public:
	MovingComponent() {}

	virtual void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	MovingComponent* Clone() { return new MovingComponent(*this); }

	void Initialize() override;
	void Update() override;

	bool OnCollision(const Event<Entity>& event);

protected:
	int score_;
	float torque_ = 0.0f;
	vector2 force_;

	vector2 force_range_;
	vector2 torque_range_;

	Handle collision_event_handle_;
};

