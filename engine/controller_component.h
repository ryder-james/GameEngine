#pragma once
#include "component.h"

class ControllerComponent : public Component
{
public:
	ControllerComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	ControllerComponent* Clone() override { return new ControllerComponent(*this); }

	void Update() override;
};
