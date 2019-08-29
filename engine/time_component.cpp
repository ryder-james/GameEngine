#include "time_component.h"

#include "entity.h"

void TimeComponent::Initialize() {}

void TimeComponent::Destroy() {}

bool TimeComponent::Load(const rapidjson::Value& value) {
	json::get(value, "time_scale", time_scale_);

	std::string token_string;
	json::get(value, "actions", token_string);

	std::vector<std::string> tokens;
	tokenize(token_string, '|', tokens);

	for (std::string& token : tokens) {
		token = "k" + token;
	}

	property_t<Action> actions[] =
	{
		REFLECT_FORM(kPlayOnce),
		REFLECT_FORM(kDestroyOwner),
		REFLECT_FORM(kRepeat),
		REFLECT_FORM(kPlayBack),
		REFLECT_FORM(kReverse)
	};

	action_ |= CreateBitMask<property_t<Action>>(actions, sizeof(actions) / sizeof(property_t<Action>), tokens);

	if (action_[kPlayOnce]) action_[kRepeat] = false;

	return true;
}

void TimeComponent::Update() {
	float direction_multiplier = (action_[kReverse]) ? -1.0f : 1.0f;
	time_ += g_timer.dt * (direction_multiplier * time_scale_);

	if (!completed_ && (time_ < 0.0f || time_ > 1.0f)) {
		if (action_[kRepeat]) {
			if (action_[kPlayBack]) {
				action_[kReverse] = !action_[kReverse];
			}
			time_ = (!action_[kReverse] ? 0.0f : 1.0f);
		} else {
			if (action_[kPlayBack]) {
				if (action_[kDestroyOwner]) owner_->state_[Entity::kDestroy] = completed_;
				completed_ = !completed_;
				action_[kReverse] = !action_[kReverse];
			} else {
				if (action_[kDestroyOwner]) owner_->state_[Entity::kDestroy] = true;
				completed_ = true;
			}

		}
	}
	if (completed_ && !action_[kDestroyOwner]) {
		time_ = (!action_[kReverse] ? 0.0f : 1.0f);
	}
}
