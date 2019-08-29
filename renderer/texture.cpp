#include "texture.h"

#include "..\\core\filesystem.h"

Texture::~Texture() {
	Texture::Destroy();
}

bool Texture::Create(const Name& image_name) {
	bool start_success = true;

 	texture_ = IMG_LoadTexture(renderer_->GetSDLRenderer(), image_name.c_str());

	return start_success;
}

bool Texture::CreateFromFont(Font* font, const char* string, const color& font_color) {
	SDL_Color color;
	color.r = static_cast<Uint8>(font_color.r);
	color.g = static_cast<Uint8>(font_color.g);
	color.b = static_cast<Uint8>(font_color.b);
	color.a = 255;

	SDL_Surface* surface = TTF_RenderText_Solid(font->font_, string, color);
	ASSERT(surface);
	texture_ = SDL_CreateTextureFromSurface(renderer_->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);

	return (texture_ != nullptr);
}

void Texture::Destroy() {
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

void Texture::Draw(const vector2& position, float angle, const vector2& scale, const vector2& origin) {
	vector2 size = GetSize();
	size = size * scale;

	vector2 screen_position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(screen_position.x);
	dest.y = static_cast<int>(screen_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	vector2 rotation_point = size * origin;
	SDL_Point pivot = { static_cast<int>(rotation_point.x), static_cast<int>(rotation_point.y) };

	SDL_RenderCopyEx(renderer_->GetSDLRenderer(), texture_, NULL, &dest, angle, &pivot, SDL_FLIP_NONE);
}

void Texture::Draw(SDL_Rect& rect, const vector2& position, float angle, const vector2& scale, const vector2& origin) {
	vector2 size = GetSize();
	size = size * scale;

	vector2 screen_position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(screen_position.x);
	dest.y = static_cast<int>(screen_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y * renderer_->GetAspectRatio());

	vector2 rotation_point = size * origin;
	SDL_Point pivot = { static_cast<int>(rotation_point.x), static_cast<int>(rotation_point.y) };

	SDL_RenderCopyEx(renderer_->GetSDLRenderer(), texture_, &rect, &dest, angle, &pivot, SDL_FLIP_NONE);
}

vector2 Texture::GetSize() const {
	SDL_Point point;

	SDL_QueryTexture(texture_, 0, 0, &point.x, &point.y);

	return vector2(point.x, point.y);
}
