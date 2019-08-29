#include "weapon_component.h"

#include "physics_component.h"
#include "engine.h"
#include "scene.h"

#include "..\\audio\audio_system.h"
#include "..\\core\timer.h"

void WeaponComponent::Destroy() {
	owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->Unsubscribe("collision", collision_handle_);
}

bool WeaponComponent::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "force", force_);
	success = json::get(value, "rate", rate_);

	return success;
}

void WeaponComponent::Initialize() {
	collision_handle_ = owner_->GetScene()->GetEngine()->GetSystem<EntityEventDispatcher>()->
		Subscribe("collision", std::bind(&WeaponComponent::OnCollision, this, std::placeholders::_1));
}

void WeaponComponent::Update() {
	PhysicsComponent* component = owner_->GetComponent<PhysicsComponent>();

	if (component) {
		vector2 force = vector2::rotate(vector2(0.0f, force_), owner_->GetTransform().rotation);
		component->AddForce(force, PhysicsComponent::kVelocity);
	}
}

bool WeaponComponent::OnCollision(const Event<Entity>& event) {
	if (event.receiver == owner_ && event.sender->GetTag() == "ant") {
		owner_->state_.set(Entity::kDestroy);
	}

	return true;
}
