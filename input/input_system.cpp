#include "input_system.h"

bool InputSystem::Startup() {
	keyboard_state_ = SDL_GetKeyboardState(NULL);

	return true;
}

void InputSystem::Shutdown() {}

void InputSystem::Update() {}

bool InputSystem::GetKey(SDL_Scancode scancode) {
	return keyboard_state_[scancode];
}
