#pragma once
#include "..\\engine\engine.h"
#include "..\\framework\state_machine.h"

class Game {
public:
	Game(Engine* engine) : engine_(engine) {}
	~Game() {}

	bool Startup();
	void Shutdown();
	void Update();

	bool Quit() { return quit_; }

protected:
	void TitleState_Enter();
	void TitleState_Update();
	void TitleState_Exit();

	void StartState_Enter();
	void StartState_Update();

	bool OnScore(const Event<Entity>& event);

protected:
	size_t score_ = 0;
	size_t lives_ = 4;

	Handle score_event_handle_;

	bool quit_ = false;
	Engine* engine_ = nullptr;
	StateMachine<Game>* state_machine_;
};
