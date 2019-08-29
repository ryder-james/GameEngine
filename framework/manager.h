#pragma once

#include "..\\core\name.h"

template <typename T, size_t N = 65536>
class Manager {
public:
	Manager() {}
	virtual ~Manager() {}

	virtual void Remove(const Name& name) = 0;
	virtual void RemoveAll() = 0;

protected:
	T* elements_[N];
};