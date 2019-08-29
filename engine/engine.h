#pragma once

#include "entity.h"
#include "..\\input\input_system.h"
#include "..\\renderer\texture.h"
#include "..\\audio\audio_system.h"
#include "..\\resource\resource_manager.h"

class Scene;

class EntityEventDispatcher : public EventDispatcher<Event<Entity>> {
public:
	EntityEventDispatcher(Engine* engine) : EventDispatcher<Event<Entity>>(engine) {}
};

class Engine {
public:
	Engine() {}
	~Engine() {}

	bool Startup();
	void Update();
	void Shutdown();

	bool LoadScene(const char* scene_name);
	void DestroyScene();
	Scene* GetScene() { return scene_; }

	bool Quit() const { return quit_; }

	ResourceManager<Resource>* GetResourceManager() { return resource_mgr_; }

	template <typename T>
	T* GetSystem() {
		T* system = nullptr;

		for (System* _system : systems_) {
			system = dynamic_cast<T*>(_system);
			if (system != nullptr) break;
		}

		return system;
	}

private:
	bool quit_ = false;

	std::vector<System*> systems_;

	Scene* scene_ = nullptr;
	ResourceManager<Resource>* resource_mgr_ = nullptr;
};