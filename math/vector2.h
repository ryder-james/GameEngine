#pragma once

#include "math.h"
#include "..\\core\assert.h"

struct vector2
{
	float x = 0;
	float y = 0;

	vector2() {}
	vector2(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
	vector2(float x, float y) : x(x), y(y) {}

	void set(float x, float y) { this->x = x; this->y = y; }

	float operator [] (size_t index) const
	{
		ASSERT(index <= 1);
		return (&x)[index];
	}

	float& operator [] (size_t index)
	{
		ASSERT(index <= 1);
		return (&x)[index];;
	}

	// relational operator
	bool operator == (const vector2 & v) const { return x == v.x && y == v.y; }
	bool operator != (const vector2 & v) const { return x != v.x || y != v.y; }
	
	// assignment operator
	// v1 += v2 -> v1 = v1 + v2;
	vector2& operator += (const vector2 & v) { x += v.x; y += v.y; return *this; }
	vector2& operator -= (const vector2 & v) { x -= v.x; y -= v.y; return *this; }

	vector2& operator += (float s) { x += s; y += s; return *this; }
	vector2& operator -= (float s) { x -= s; y -= s; return *this; }
	vector2& operator *= (float s) { x *= s; y *= s; return *this; }
	vector2& operator /= (float s) { x /= s; y /= s; return *this; }

	// arithmetic operator
	vector2 operator + (const vector2 & v) const { return vector2(x + v.x, y + v.y); }
	vector2 operator - (const vector2 & v) const { return vector2(x - v.x, y - v.y); }
	vector2 operator * (const vector2 & v) const { return vector2(x * v.x, y * v.y); }
	vector2 operator / (const vector2 & v) const { return vector2(x / v.x, y / v.y); }

	vector2 operator + (float s) const { return vector2(x + s, y + s); }
	vector2 operator - (float s) const { return vector2(x - s, y - s); }
	vector2 operator * (float s) const { return vector2(x * s, y * s); }
	vector2 operator / (float s) const { return vector2(x / s, y / s); }
	
	vector2& operator - (void) { x = -x; y = -y; return *this; }

	inline float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline float length_sqr() const
	{
		return ((x * x) + (y * y));
	}

	inline vector2 normalized() const
	{
		float vlength = length();
		vector2 normalize = (vlength == 0.0f) ? vector2(0.0f, 0.0f) : (*this / vlength);

		return normalize;
	}

	inline const vector2& normalize()
	{
		float vlength = length();
		if (vlength == 0.0f)
		{
			*this = zero;
		}
		else
		{
			*this /= vlength;
		}

		return *this;
	}
	
	inline static float distance(const vector2& v1, const vector2& v2)
	{
		
		vector2 v = v1 - v2;
		return v.length();
	}

	inline static float distance_sqr(const vector2& v1, const vector2& v2)
	{
		vector2 v = v1 - v2;
		return v.length_sqr();
	}
	
	inline static float dot(const vector2& v1, const vector2& v2)
	{
		return ((v1.x * v2.x) + (v1.y * v2.y));
	}

	inline static vector2 rotate(const vector2& v1, float angle)
	{
		float x = v1.x * std::cos(angle) - v1.y * std::sin(angle);
		float y = v1.x * std::sin(angle) + v1.y * std::cos(angle);

		return vector2(x, y);
	}

	inline static float get_angle(const vector2& v)
	{
		return std::atan2(v.y, v.x);
	}

	static const vector2 zero;
	static const vector2 one;
	static const vector2 up;
	static const vector2 down;
	static const vector2 left;
	static const vector2 right;
};

