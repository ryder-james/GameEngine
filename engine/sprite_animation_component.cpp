#include "sprite_animation_component.h"

#include "engine.h"
#include "scene.h"
#include "time_component.h"
#include "physics_component.h"

#include "..\\renderer\texture.h"

bool SpriteAnimationComponent::Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin) {
	name_ = name;
	owner_ = owner;
	texture_name_ = texture_name;
	origin_ = origin;

	return true;
}

void SpriteAnimationComponent::Destroy() {}

bool SpriteAnimationComponent::Load(const rapidjson::Value& value) {
	RenderComponent::Load(value);

	bool success;

	success = json::get(value, "texture_name", texture_name_);
	success = json::get(value, "origin", origin_);
	success = json::get(value, "total_frames", frame_count_);
	success = json::get(value, "frames_per_col", frames_per_col_);
	success = json::get(value, "frames_per_row", frames_per_row_);

	return success;
}

void SpriteAnimationComponent::Initialize() {
	texture_ = owner_->GetScene()->GetEngine()->GetResourceManager()->Get<Texture>(texture_name_);
}

void SpriteAnimationComponent::Update() {
 	TimeComponent* component = owner_->GetComponent<TimeComponent>();
	float time = component->GetTime();
	current_frame_ = static_cast<int>(time * frame_count_);

	vector2 texture_size = texture_->GetSize();
	vector2 frame_num(frames_per_row_, frames_per_col_);

	vector2 frame_size = texture_size / frame_num;

	rect_.x = static_cast<int>((current_frame_ % frames_per_row_) * frame_size.x);
	rect_.y = static_cast<int>((current_frame_ / frames_per_row_) * frame_size.y);

	rect_.w = static_cast<int>(frame_size.x);
	rect_.h = static_cast<int>(frame_size.y);
}

void SpriteAnimationComponent::Draw() {
	transform owner_t = owner_->GetTransform();
	texture_->Draw(rect_, owner_t.translation, owner_t.rotation * math::RAD_TO_DEG, owner_t.scale, origin_);
}

void SpriteAnimationComponent::Reset() {
	TimeComponent* component = owner_->GetComponent<TimeComponent>();
	component->Reset();
}
