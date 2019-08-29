#include "engine.h"

#include "entity.h"
#include "scene.h"

#include "..\\renderer\particle_system.h"

#include "..\\core\filesystem.h"

bool Engine::Startup() {
	Name::AllocNames();
	filesystem::set_current_path("../");

	bool start_success = true;

	AudioSystem* audio_system = new AudioSystem(this);
	start_success = audio_system->Startup();
	systems_.push_back(audio_system);

	Renderer* renderer = new Renderer(this);
	start_success = renderer->Startup();
	if (start_success) renderer->Create("game", 800, 600);
	systems_.push_back(renderer);

	InputSystem* input = new InputSystem(this);
	start_success = input->Startup();
	systems_.push_back(input);

	EntityEventDispatcher* dispatcher = new EntityEventDispatcher(this);
	dispatcher->Startup();
	systems_.push_back(dispatcher);

	ParticleSystem* particle_s = new ParticleSystem(this);
	particle_s->Startup();
	systems_.push_back(particle_s);

	resource_mgr_ = new ResourceManager<Resource>(renderer);

	return start_success;
}

void Engine::Update() {
	for (System* system : systems_) {
		system->Update();
	}

	SDL_Event e;
	if (SDL_PollEvent(&e) || GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_ESCAPE)) {
		quit_ = (e.type == SDL_QUIT) || GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_ESCAPE);
	}

	if (scene_) scene_->Update();

	GetSystem<Renderer>()->BeginFrame();
	if (scene_) scene_->Draw();

	GetSystem<ParticleSystem>()->Draw();

	GetSystem<Renderer>()->EndFrame();

	g_timer.tick();
}

void Engine::Shutdown() {
	DestroyScene();

	delete resource_mgr_;

	for (System* system : systems_) {
		system->Shutdown();
		delete system;
	}
	systems_.clear();

	Name::FreeNames();

	SDL_Quit();
}

bool Engine::LoadScene(const char* scene_name) {
	scene_ = new Scene();
	scene_->Create("scene", this);

	rapidjson::Document document;
	json::load(scene_name, document);
	scene_->Load(document);

	scene_->Initialize();

	return true;
}

void Engine::DestroyScene() {
	if (scene_) {
		scene_->Destroy();
		delete scene_;
		scene_ = nullptr;
	}
}

