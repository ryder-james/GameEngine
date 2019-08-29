#include "circle_collision_component.h"

#include "entity.h"

void CircleCollisionComponent::Create(const Name& name, Entity* owner, float radius) {}

void CircleCollisionComponent::Destroy() {}

bool CircleCollisionComponent::Load(const rapidjson::Value& value) {
	json::get(value, "radius", radius_);

	return true;
}

void CircleCollisionComponent::Update() {}

bool CircleCollisionComponent::Intersects(CollisionComponent* other) {
	bool intersects = false;

	CircleCollisionComponent* component = dynamic_cast<CircleCollisionComponent*>(other);
	if (component) {
		float distance = vector2::distance(owner_->GetTransform().translation, other->GetOwner()->GetTransform().translation);
		if (distance <= radius_ + component->radius_) {
			intersects = true;
		}
	}

	return intersects;
}
