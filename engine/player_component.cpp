#include "player_component.h"

#include "scene.h"

#include "..\\core\timer.h"

void PlayerComponent::Destroy() {
	owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Unsubscribe("fire_weapon", fire_handle_);
	owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Unsubscribe("collision", collision_handle_);
}

bool PlayerComponent::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "fire_rate", fire_rate_);
	fire_timer_ = fire_rate_;

	return success;
}

void PlayerComponent::Initialize() {
	collision_handle_ = owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->
		Subscribe("collision", std::bind(&PlayerComponent::OnCollision, this, std::placeholders::_1));
	fire_handle_ = owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->
		Subscribe("fire_weapon", std::bind(&PlayerComponent::FireWeapon, this));
}

void PlayerComponent::Update() {
	fire_timer_ -= g_timer.dt;
}

bool PlayerComponent::FireWeapon() {
	if (fire_timer_ <= 0) {
		Entity* laser = owner_->GetScene()->GetObjectFactory()->Create<Entity>("bullet");

		laser->GetTransform().translation = owner_->GetTransform().translation;
		laser->GetTransform().rotation = owner_->GetTransform().rotation;

		owner_->GetScene()->Add(laser);

		fire_timer_ = fire_rate_;
	}

	return true;
}

bool PlayerComponent::OnCollision(const Event<Entity>& event) {
	if (event.sender == owner_ && event.receiver->GetTag() == "asteroid") {

	}

	return true;
}
