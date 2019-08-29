#pragma once
#include "component.h"

class WeaponComponent : public Component
{
public:
	WeaponComponent() {}

	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new WeaponComponent(*this); }

	void Initialize() override;

	void Update() override;

	bool OnCollision(const Event<Entity>& event);

protected:
	float force_;
	float rate_;

private:
	Handle collision_handle_;
};

