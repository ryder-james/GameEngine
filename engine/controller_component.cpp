#include "controller_component.h"

#include "scene.h"
#include "engine.h"
#include "physics_component.h"
#include "sprite_animation_component.h"
#include "time_component.h"

#include "..\\external\SDL2-2.0.10\include\SDL.h"

void ControllerComponent::Destroy() {}

bool ControllerComponent::Load(const rapidjson::Value& value) {
	return true;
}

void ControllerComponent::Update() {
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

	vector2 force = vector2::zero;
	float torque = 0.0f;

	if (keyboard_state[SDL_SCANCODE_A]) torque -= 15.0f;
	if (keyboard_state[SDL_SCANCODE_D]) torque += 15.0f;

	float time = owner_->GetComponent<TimeComponent>()->GetTime();

	if (time == 0.0f && keyboard_state[SDL_SCANCODE_SPACE]) {
		owner_->GetComponent<SpriteAnimationComponent>()->Reset();
	}

	if (time > 0.6 && time < 0.8) {
		Event<Entity> event;
		event.name = "fire_weapon";

		owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Notify(event);
	}

	PhysicsComponent* component = owner_->GetComponent<PhysicsComponent>();
	vector2 r_force = vector2::rotate(force, owner_->GetTransform().rotation);
	component->AddForce(r_force, PhysicsComponent::kForce);
	component->AddTorque(torque, PhysicsComponent::kVelocity);
}
