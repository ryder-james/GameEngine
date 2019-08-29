#pragma once
#include "component.h"

class RenderComponent : public Component {
public:
	RenderComponent() : Component() {}

	virtual void Draw() = 0;
	virtual bool Load(const rapidjson::Value& value) override;

	static bool SortZ(const RenderComponent* lhs, const RenderComponent* rhs) {
		return lhs->z < rhs->z;
	}

protected:
	int z = 0;
};
