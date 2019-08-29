#pragma once

#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

struct Particle {
	vector2 position;
	vector2 prev_position;
	vector2 velocity;

	color color;

	float damping;
	float lifetime;

	bool active;
};