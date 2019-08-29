#pragma once

#include "actor.h"

class Missile : public Actor {
public:
	Missile() {}
	virtual ~Missile() {}

	const char* GetType() {
		return "Missile";
	}

	virtual void Update(float dt) override;

	bool Load(const rapidjson::Value& value) override;
};