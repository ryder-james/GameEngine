#pragma once
#include "render_component.h"

class SpriteComponent : public RenderComponent {
public:
	SpriteComponent() {}

	bool Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin = vector2::zero);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	SpriteComponent* Clone() override { return new SpriteComponent(*this); }

	void Update() override;
	void Draw() override;

private:
	Name texture_name_;
	vector2 origin_;
};
