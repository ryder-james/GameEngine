#include "text_component.h"

#include "engine.h"
#include "scene.h"
#include "..\\renderer\font.h"
#include "..\\renderer\texture.h"

bool TextComponent::Create(const Name& name, Entity* owner, const Name& font_name) {
	name_ = name;
	owner_ = owner;
	font_name_ = font_name;

	return true;
}

void TextComponent::Destroy() {}

bool TextComponent::Load(const rapidjson::Value& value) {
	RenderComponent::Load(value);

	bool success;

	success = json::get(value, "font_name", font_name_);
	success = json::get(value, "color", color_);
	success = json::get(value, "origin", origin_);
	success = json::get(value, "texture_name_base", texture_name_base_);
	success = json::get(value, "text", text_);

	return success;
}

void TextComponent::Initialize() {
	Font* font = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Font>(font_name_);
	Texture* texture = new Texture(owner_->GetScene()->GetEngine()->GetSystem<Renderer>());

	texture_name_ = Name(texture_name_base_.c_str(), true);
	owner_->GetScene()->GetEngine()->GetResourceManager()->Add(texture_name_, texture);

	SetText(text_.c_str());
}

void TextComponent::Update() {}

void TextComponent::Draw() {
	Texture* texture = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(texture_name_);
	transform owner_t = owner_->GetTransform();
	texture->Draw(owner_t.translation, owner_t.rotation * math::RAD_TO_DEG, owner_t.scale);
}

void TextComponent::SetText(const char* string) {
	text_ = string;

	Font* font = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Font>(font_name_);
	Texture* texture = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(texture_name_);

	texture->CreateFromFont(font, text_.c_str(), color_);
}
