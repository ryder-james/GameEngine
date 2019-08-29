#pragma once
#include "collision_component.h"

class CircleCollisionComponent : public CollisionComponent {
public:
	CircleCollisionComponent() : CollisionComponent() {}

	void Create(const Name& name, Entity* owner, float radius);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new CircleCollisionComponent(*this); }

	void Update() override;

	bool Intersects(CollisionComponent* other);

protected:
	float radius_;
};