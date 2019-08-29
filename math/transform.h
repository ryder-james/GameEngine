#pragma once

#include "matrix33.h"
#include "..\\core\core.h"

struct transform {
	vector2 translation;
	float rotation = 0;
	vector2 scale;

	matrix33 mxWorld;

	transform() {}
	transform(vector2& translation, float rotation, vector2 scale) : 
		translation(translation), 
		rotation(rotation), 
		scale(scale) {}

	bool Load(const rapidjson::Value& value);
	bool Update();

	void Update(const transform& parent, const transform& local);
};