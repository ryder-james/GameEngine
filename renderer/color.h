#pragma once

#include "..\\math\math.h"
#include "..\\core\assert.h"

#include <windows.h>

struct color {
public:
	float r, g, b;

	color() {
		r = 0;
		g = 0;
		b = 0;
	}
	color(float r, float g, float b) : r(r), g(g), b(b) {}

	void set(float r, float g, float b);

	float operator [](size_t index) const {
		ASSERT(index < 3);
		switch (index) {
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		}
	}

	float& operator [](size_t index) {
		ASSERT(index < 3);
		switch (index) {
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		}
	}

	bool operator ==(const color& c) const {
		return r == c.r && g == c.g && b == c.b;
	}

	bool operator !=(const color& c) const {
		return !(operator ==(c));
	}

	color& operator +=(const color& c) {
		r += c.r;
		g += c.g;
		b += c.b;

		return *this;
	}
	color& operator -=(const color& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;

		return *this;
	}

	color& operator *=(const color& c) {
		r *= c.r;
		g *= c.g;
		b *= c.b;

		return *this;
	}
	color& operator /=(const color& c) {
		r /= c.r;
		g /= c.g;
		b /= c.b;

		return *this;
	}

	color& operator +=(float s) {
		r += s;
		g += s;
		b += s;

		return *this;
	}
	color& operator -=(float s) {
		r -= s;
		g -= s;
		b -= s;

		return *this;
	}
	color& operator *=(float s) {
		r *= s;
		g *= s;
		b *= s;

		return *this;
	}
	color& operator /=(float s) {
		r /= s;
		g /= s;
		b /= s;

		return *this;
	}

	color operator +(const color& c) const {
		return color(r + c.r, g + c.g, b + c.b);
	}
	color operator -(const color& c) const {
		return color(r - c.r, g - c.g, b - c.b);
	}
	color operator *(const color& c) const {
		return color(r * c.r, g * c.g, b * c.b);
	}
	color operator /(const color& c) const {
		return color(r / c.r, g / c.g, b / c.b);
	}

	color operator +(float s) const {
		return color(r + s, g + s, b + s);
	}
	color operator -(float s) const {
		return color(r - s, g - s, b - s);
	}
	color operator *(float s) const {
		return color(r * s, g * s, b * s);
	}
	color operator /(float s) const {
		return color(r / s, g / s, b / s);
	}

	operator COLORREF() const {
		BYTE _r = static_cast<BYTE>(math::clamp01(r) * 255.0f);
		BYTE _g = static_cast<BYTE>(math::clamp01(g) * 255.0f);
		BYTE _b = static_cast<BYTE>(math::clamp01(b) * 255.0f);

		return RGB(_r, _g, _b);
	}

	static const color red;
	static const color green;
	static const color blue;
	static const color white;
	static const color orange;
	static const color yellow;
	static const color magenta;
	static const color cyan;
};