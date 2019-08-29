#pragma once

#include "render_component.h"

class TextComponent : public RenderComponent {
public:
	TextComponent() {}

	bool Create(const Name& name, Entity* owner, const Name& font_name);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	TextComponent* Clone() override { return new TextComponent(*this); }

	void Initialize() override;

	void Update() override;
	void Draw() override;

	void SetText(const char* string);

private:
	Name font_name_;
	Name texture_name_;
	color color_;
	vector2 origin_;

	std::string text_;
	std::string texture_name_base_;
};