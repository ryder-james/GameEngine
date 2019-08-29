#pragma once

#include "..\\core\core.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

struct Particle {
	Name texture_name;
	vector2 position;
	vector2 velocity;
	float scale = 1.0f;
	float damping = 0.995f;
	float lifetime;
	float lifetimer;
	bool active = false;
};