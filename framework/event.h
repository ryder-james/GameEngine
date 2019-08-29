#pragma once

#include "variant.h"

template<typename T>
struct Event {
	Name name;
	T* sender;
	T* receiver;

	Variant data[3];
};