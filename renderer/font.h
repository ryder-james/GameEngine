#pragma once

#include "renderer.h"
#include "..\\renderer\color.h"
#include "..\\resource\resource.h"
#include "..\\core\name.h"

class Font : public Resource {
public:
	Font(Renderer* renderer) : renderer_(renderer) {}
	~Font();

	bool Create(const Name& font_name);
	void Destroy();

	friend class Texture;

protected:
	Renderer* renderer_;
	TTF_Font* font_ = nullptr;
};