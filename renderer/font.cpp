#include "font.h"
#include "..\\core\assert.h"

Font::~Font() {}

bool Font::Create(const Name& font_name) {
	font_ = TTF_OpenFont(font_name.c_str(), 32);
	ASSERT(font_);

	return true;
}

void Font::Destroy() {
	if (font_) {
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}
