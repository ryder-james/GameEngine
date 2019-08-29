#pragma once

#include "..\\engine\system.h"
#include "..\\external\fmod\api\core\inc\fmod.hpp"

#include <string>
#include <map>

class AudioSystem : public System {
public:
	AudioSystem(Engine* engine) : System(engine) {}
	~AudioSystem() {}

	bool Startup() override;
	void Update() override;
	void Shutdown() override;

	void AddSound(const std::string& key, const char* filename);
	void Play(const std::string& key, bool loop = false);
	void RemoveSound(const std::string& key);

private:
	FMOD::System* system_ = nullptr;
	std::map<std::string, FMOD::Sound*> sounds_;
};