#pragma once

#include "..\\core\name.h"

class Resource {
public:
	Resource() {}
	virtual ~Resource() {}

	virtual bool Create(const Name& name) = 0;
	virtual void Destroy() = 0;
};