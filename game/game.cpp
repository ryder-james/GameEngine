#include "game.h"

#include "..\\engine\scene.h"
#include "..\\engine\text_component.h"

bool Game::Startup() {
	bool success = engine_->Startup();

	score_event_handle_ = engine_->GetSystem<EntityEventDispatcher>()
		->Subscribe("score", std::bind(&Game::OnScore, this, std::placeholders::_1));

	state_machine_ = new StateMachine<Game>(this);

	{
		State title_state;
		title_state.Enter = std::bind(&Game::TitleState_Enter, this);
		title_state.Update = std::bind(&Game::TitleState_Update, this);
		title_state.Exit = std::bind(&Game::TitleState_Exit, this);
		state_machine_->AddState("title", title_state);
	}

	{
		State start_state;
		start_state.Enter = std::bind(&Game::StartState_Enter, this);
		start_state.Update = std::bind(&Game::StartState_Update, this);
		state_machine_->AddState("start", start_state);
	}

	state_machine_->SetState("title");

	return success;
}

void Game::Shutdown() {
	engine_->Shutdown();

	delete engine_;

	delete state_machine_;
}

void Game::Update() {
	engine_->Update();
	quit_ = engine_->Quit();

	state_machine_->Update();
}

void Game::TitleState_Enter() {
	engine_->LoadScene("scenes/astro_blasters_title.json");
}

void Game::TitleState_Update() {
	if (engine_->GetSystem<InputSystem>()->GetKey(SDL_SCANCODE_SPACE)) {
		state_machine_->SetState("start");
	}
}

void Game::TitleState_Exit() {
	engine_->DestroyScene();
}

void Game::StartState_Enter() {
	engine_->LoadScene("scenes/picnic.json");

	for (size_t i = 0; i < 10; i++) {
		Entity* entity = engine_->GetScene()->GetObjectFactory()->Create<Entity>("ant");
		entity->GetTransform().translation = vector2(g_random(800), g_random(600));
		engine_->GetScene()->Add(entity);
	}
}

void Game::StartState_Update() {}

bool Game::OnScore(const Event<Entity>& event) {
	score_ += event.data[0].as_int;
	Entity* entity = engine_->GetScene()->GetEntityWithName("score");
	std::string score = std::to_string(score_);
	entity->GetComponent<TextComponent>()->SetText(score.c_str());

	return true;
}
