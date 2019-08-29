#pragma once

#include "component.h"

class AudioComponent : public Component {
public:
	struct AudioClip {
		AudioClip(Name& audio_name, Name& file_name) : 
			audio_name_(audio_name),
			file_name_(file_name)
		{}

		Name audio_name_;
		Name file_name_;
	};
public:
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	AudioComponent* Clone() { return new AudioComponent(*this); }

	void Initialize() override;
	void Update() override;

	void Play(int index);
	void Play(const Name& name);
	void PlayNext();
	void PlayRandom();

private:
	std::vector<AudioClip> audio_clips_;

	int play_tracker_;
};