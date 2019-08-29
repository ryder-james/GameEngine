#pragma once
#include "component.h"

class TimeComponent : public Component {
public:
	enum Action {
		kPlayOnce,
		kDestroyOwner,
		kRepeat,
		kPlayBack,
		kReverse
	};

public:
	TimeComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new TimeComponent(*this); }

	void Update() override;

	float GetTime() { return time_; }
	void SetTimeScale(float time_scale) { time_scale_ = time_scale; }
	float GetTimeScale() { return time_scale_; }

	void Reset() { time_ = (!action_[kRepeat] ? 0.0f : 1.0f); completed_ = false; }

protected:
	bit_mask_t action_ = BIT(kRepeat);
	float time_ = 0.0f;
	float time_scale_ = 1.0f;
	bool completed_ = false;
};