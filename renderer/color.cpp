#include "color.h"

const color color::red = color(255, 0, 0);
const color color::green = color(0, 255, 0);
const color color::blue = color(0, 0, 255);
const color color::white = color(255, 255, 255);
const color color::orange = color(255, 165, 0);
const color color::yellow = color(255, 255, 0);
const color color::magenta = color(255, 0, 255);
const color color::cyan = color(0, 255, 255);

void color::set(float r, float g, float b) {
	color::r = r;
	color::g = g;
	color::b = b;
}
