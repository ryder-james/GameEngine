#include "audio_system.h"

#include "..\\core\assert.h"

bool AudioSystem::Startup() {
	FMOD_RESULT result = FMOD::System_Create(&system_);
	ASSERT_MSG(result == FMOD_OK, "Error creating FMOD system");

	void* extra_driver_data = nullptr;
	result = system_->init(32, FMOD_INIT_NORMAL, extra_driver_data);
	ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system");

	return true;
}

void AudioSystem::Shutdown() {

	if (sounds_.size() > 0) {
		for (auto& sound : sounds_) {
			sound.second->release();
		}

		sounds_.clear();
	}

		FMOD_RESULT result = system_->close();
		ASSERT_MSG(result == FMOD_OK, "Error closing FMOD system");

		result = system_->release();
		ASSERT_MSG(result == FMOD_OK, "Error releasing FMOD system");

}

void AudioSystem::Update() {
	FMOD_RESULT result = system_->update();
	ASSERT_MSG(result == FMOD_OK, "Error updating FMOD system");
}

void AudioSystem::AddSound(const std::string& key, const char* filename) {
	if (sounds_.find(key) == sounds_.end()) {
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = system_->createSound(filename, FMOD_DEFAULT, 0, &sound);
		if (result == FMOD_OK) {
			sounds_[key] = sound;
		}
	}
}

void AudioSystem::Play(const std::string& key, bool loop) {
	auto iter = sounds_.find(key);
	if (iter != sounds_.end()) {
		FMOD::Sound* sound = iter->second;
		FMOD_MODE mode = (loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
		sound->setMode(mode);

		FMOD::Channel* channel;

		FMOD_RESULT result = system_->playSound(sound, 0, false, &channel);
		ASSERT_MSG(result == FMOD_OK, "Error playing sound");
	}
}

void AudioSystem::RemoveSound(const std::string& key) {
	auto iter = sounds_.find(key);
	if (iter != sounds_.end()) {
		iter->second->release();
		sounds_.erase(iter);
	}
}
