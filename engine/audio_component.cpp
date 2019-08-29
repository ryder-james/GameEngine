#include "audio_component.h"

#include "scene.h"
#include "engine.h"

void AudioComponent::Destroy() {}

bool AudioComponent::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "spawn_clip_index", play_tracker_);

	const rapidjson::Value& audio_files_value = value["audio_files"];
	if (audio_files_value.IsArray()) {
		for (rapidjson::SizeType i = 0; i < audio_files_value.Size(); i++) {
			const rapidjson::Value& audio_file_val = audio_files_value[i];
			if (audio_file_val.IsObject()) {
				Name audio_name;
				Name audio_file_name;
				json::get(audio_file_val, "audio_name", audio_name);
				json::get(audio_file_val, "audio_file_name", audio_file_name);

				audio_clips_.push_back(AudioClip(audio_name, audio_file_name));
			}
		}
	}

	return success;
}

void AudioComponent::Initialize() {
	for (AudioClip clip : audio_clips_) {
		owner_->GetScene()->GetEngine()->GetSystem<AudioSystem>()->AddSound(clip.audio_name_.c_str(), clip.file_name_.c_str());
	}

	if (play_tracker_ >= 0) {
		Play(play_tracker_);
	}
}

void AudioComponent::Update() {}

void AudioComponent::Play(int index) {
	ASSERT(index >= 0 && index < audio_clips_.size());

	Play(audio_clips_[index].audio_name_);
	play_tracker_ = (play_tracker_ + 1) % static_cast<int>(audio_clips_.size());
}

void AudioComponent::Play(const Name& audio_name) {
	for (int i = 0; i < audio_clips_.size(); i++) {
		if (audio_clips_[i].audio_name_ == audio_name) {
			play_tracker_ = i;
			break;
		}
	}

	owner_->GetScene()->GetEngine()->GetSystem<AudioSystem>()->Play(audio_name.c_str());
}

void AudioComponent::PlayNext() {
	Play(play_tracker_);
}

void AudioComponent::PlayRandom() {
	Play(g_random_int(static_cast<int>(audio_clips_.size()) - 1));
}
