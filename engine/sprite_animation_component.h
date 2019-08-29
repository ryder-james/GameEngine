#pragma once

#include "render_component.h"

#include "..\\external\SDL2-2.0.10\include\SDL.h"

class Texture;

class SpriteAnimationComponent : public RenderComponent {
public:
	SpriteAnimationComponent() {}

	bool Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin = vector2::zero);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	SpriteAnimationComponent* Clone() override { return new SpriteAnimationComponent(*this); }

	void Initialize() override;

	void Update() override;
	void Draw() override;

	void Reset();

private:
	Texture* texture_ = nullptr;
	Name texture_name_;
	vector2 origin_;
	SDL_Rect rect_;

	int frame_count_ = 1;
	int frames_per_col_ = 1;
	int frames_per_row_ = 1;

	int current_frame_ = 0;
	float frame_timer_ = 0.0f;
	float frame_rate_ = 1.0f / 30.0f; // 1 second divided by 30 frames - 30fps

	bool completed_animation_ = false;
};
