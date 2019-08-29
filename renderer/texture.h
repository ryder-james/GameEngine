#pragma once

#include "renderer.h"
#include "font.h"
#include "..\\math\vector2.h"
#include "..\\resource\resource.h"

class Texture : public Resource {
public:
	Texture(Renderer* renderer) : renderer_(renderer) {}
	~Texture();

	bool Create(const Name& image_name) override;
	bool CreateFromFont(Font* font, const char* string, const color& color);
	void Destroy() override;

	void Draw(const vector2& position, float angle = 0, const vector2 & scale = vector2::one, const vector2& origin = vector2::zero);
	void Draw(SDL_Rect& rect, const vector2& position, float angle = 0, const vector2 & scale = vector2::one, const vector2& origin = vector2::zero);
	vector2 GetSize() const;

protected:
	Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};