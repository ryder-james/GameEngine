#include "game.h"

#include "..\\engine\scene.h"
#include "..\\engine\text_component.h"

bool Game::Startup() {
	bool success = engine_->Startup();

	score_event_handle_ = engine_->GetSystem<EntityEventDispatcher>()
		->Subscribe("score", std::bind(&Game::OnScore, this, std::placeholders::_1));

	monch_handle_ = engine_->GetSystem<EntityEventDispatcher>()
		->Subscribe("food_devoured", std::bind(&Game::OnMonch, this));

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
	engine_->GetSystem<EntityEventDispatcher>()->Unsubscribe("score", score_event_handle_);
	engine_->GetSystem<EntityEventDispatcher>()->Unsubscribe("food_devoured", monch_handle_);

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
}

void Game::StartState_Update() {
	if (engine_->GetScene()->GetEntitiesWithTag("ant").size() == 0) {
		SpawnAntWave(g_random_int(6, 13));
		SpawnCookieCrumb();
	}
}

bool Game::OnMonch() {
	//if (--lives_ == 0) {
	//	state_machine_->SetState("game_over");
	//}

	lives_--;

	Entity* entity = engine_->GetScene()->GetEntityWithName("lives");
	std::string lives = std::to_string(lives_);
	lives += " Lives Left";
	entity->GetComponent<TextComponent>()->SetText(lives.c_str());

	return true;
}

bool Game::OnScore(const Event<Entity>& event) {
	score_ += event.data[0].as_int;
	Entity* entity = engine_->GetScene()->GetEntityWithName("score");
	std::string score = std::to_string(score_);
	entity->GetComponent<TextComponent>()->SetText(score.c_str());

	return true;
}

void Game::SpawnAntWave(int ant_count) {
	for (int i = 0; i < ant_count; i++) {
		Entity* entity = engine_->GetScene()->GetObjectFactory()->Create<Entity>("red_ant");
		bool left = static_cast<bool>(g_random_int(1));
		bool top = static_cast<bool>(g_random_int(1));

		float x;
		float y;
		if (left) {
			x = g_random(200);
		} else {
			x = g_random(600, 800);
		}

		if (top) {
			y = g_random(150);
		} else {
			y = g_random(450, 600);
		}

		entity->GetTransform().translation = vector2(x, y);
		engine_->GetScene()->Add(entity);
	}
}

void Game::SpawnCookieCrumb() {
	Entity* crumb = engine_->GetScene()->GetObjectFactory()->Create<Entity>("crumb");
	crumb->GetTransform().translation = vector2(g_random(250, 350), g_random(200, 400));
	engine_->GetScene()->Add(crumb);
}
