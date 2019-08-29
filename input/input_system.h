#pragma once

#include "..\\engine\system.h"

#include "..\\external\SDL2-2.0.10\include\SDL.h"

class InputSystem : public System {
public:
	InputSystem(Engine* engine) : System(engine) {}
	~InputSystem() {}

	bool Startup();
	void Shutdown();

	void Update();

	bool GetKey(SDL_Scancode scancode);

private:
	const Uint8* keyboard_state_ = nullptr;
};
