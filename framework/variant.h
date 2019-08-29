#pragma once

#include "..\\math\vector2.h"
#include "..\\core\name.h"

struct Variant {
	Variant() {}

	enum Type {
		kInt,
		kFloat,
		kBool,
		kVector2,
		kName
	};

	union {
		int as_int;
		float as_float;
		bool as_bool;
		vector2 as_vector2;
		Name as_name;
	};

	Type type;
};