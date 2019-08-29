#include "emitter_component.h"

#include "scene.h"
#include "engine.h"

#include "..\\renderer\particle_system.h"

void EmitterComponent::Destroy() {}

void EmitterComponent::Update() {
	spawn_timer_ = spawn_timer_ + g_timer.dt;
	while (spawn_timer_ >= spawn_rate_) {
		spawn_timer_ = spawn_timer_ - spawn_rate_;

		float lifetime = g_random(lifetime_range_[0], lifetime_range_[1]);
		float velocity = g_random(velocity_range_[0], velocity_range_[1]);
		float angle = g_random(angle_range_[0], angle_range_[1]);

		vector2 random_direction = vector2::rotate(vector2::up, owner_->GetTransform().rotation + (angle * math::DEG_TO_RAD));
		vector2 v = random_direction * velocity;

		owner_->GetScene()->GetEngine()->GetSystem<ParticleSystem>()->Create(texture_name_, owner_->GetTransform().translation, v, damping_, lifetime);
	}
}

bool EmitterComponent::Load(const rapidjson::Value& value) {
	json::get(value, "texture_name", texture_name_);

	json::get(value, "spawn_rate", spawn_rate_);

	json::get(value, "lifetime_range", lifetime_range_);
	json::get(value, "velocity_range", velocity_range_);
	json::get(value, "angle_range", angle_range_);
	json::get(value, "damping", damping_);

	return true;
}
