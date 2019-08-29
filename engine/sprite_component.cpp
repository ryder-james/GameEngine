#include "sprite_component.h"

#include "engine.h"
#include "scene.h"
#include "..\\renderer\texture.h"

bool SpriteComponent::Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin) {
	name_ = name;
	owner_ = owner;
	texture_name_ = texture_name;
	origin_ = origin;

	return true;
}

void SpriteComponent::Destroy() {}

bool SpriteComponent::Load(const rapidjson::Value& value) {
	RenderComponent::Load(value);

	bool success;

	success = json::get(value, "texture_name", texture_name_);
	success = json::get(value, "origin", origin_);

	return success;
}

void SpriteComponent::Update() {}

void SpriteComponent::Draw() {
	Texture* texture = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(texture_name_);
	transform owner_t = owner_->GetTransform();
	texture->Draw(owner_t.translation, owner_t.rotation * math::RAD_TO_DEG, owner_t.scale, origin_);
}
