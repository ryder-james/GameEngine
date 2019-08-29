#pragma once

#include "object.h"
#include "entity.h"

class Component : public Object {
public:
	Component() {}

	void Create(const Name& name, Entity* owner) {
		name_ = name;
		owner_ = owner;
	}
	virtual void Update() = 0;

	void SetOwner(Entity* owner) { owner_ = owner; }
	Entity* GetOwner() { return owner_; }

protected:
	Entity* owner_;
};