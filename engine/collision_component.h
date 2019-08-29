#pragma once
#include "component.h"
#include "engine.h"

class CollisionComponent : public Component {
public:
	CollisionComponent() : Component() {}

	virtual bool Intersects(CollisionComponent* other) = 0;
};