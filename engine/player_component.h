#pragma once

#include "engine.h"
#include "component.h"

class PlayerComponent : public Component
{
public:
	PlayerComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new PlayerComponent(*this); }

	void Initialize() override;

	void Update() override;

	bool FireWeapon();
	bool OnCollision(const Event<Entity>& event);

protected:
	float fire_rate_ = 0.0f;
	float fire_timer_ = 0.0f;

	Handle fire_handle_;
	Handle collision_handle_;
};

