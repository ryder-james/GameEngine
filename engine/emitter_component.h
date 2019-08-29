#pragma once
#include "component.h"

class EmitterComponent : public Component {
public:
	EmitterComponent() {}
	virtual ~EmitterComponent() {}

	void Destroy() override;
	virtual bool Load(const rapidjson::Value& value) override;
	virtual EmitterComponent* Clone() { return new EmitterComponent(*this); }

	virtual void Update() override;

protected:
	Name texture_name_;
	vector2 direction_;
	float spawn_timer_ = 0.0f;

	float spawn_rate_;

	vector2 lifetime_range_;
	vector2 velocity_range_;
	vector2 angle_range_;
	float damping_;
};
