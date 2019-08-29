#pragma once

#include "vector2.h"

///Column-row indexed
struct matrix33 {
public:
	matrix33() {}

	void set_identity() {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				m[i][j] = (float)(i == j ? 1 : 0);
			}
		}
		//100
		//010
		//001
	}

	void scale(float s) {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				m[i][j] = (float)(i == j ? s : 0);
			}
		}

		m[2][2] = 1;
		//s00
		//0s0
		//001
	}

	void scale(const vector2& s) {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				m[i][j] = 0;
			}
		}

		m[0][0] = s.x;
		m[1][1] = s.y;
		m[2][2] = 1;
		//s00
		//0s0
		//001
	}

	void rotate(float angle) {
		m[0][0] = cos(angle); m[1][0] = sin(angle); m[2][0] = 0;
		m[0][1] = -sin(angle); m[1][1] = cos(angle); m[2][1] = 0;
		m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
	}

	void translate(const vector2& v) {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				m[i][j] = (float)(i == j ? 1 : 0);
			}
		}
		m[0][2] = v.x;
		m[1][2] = v.y;
		//100
		//010
		//001
	}

	matrix33 operator * (const matrix33& mx) {
		matrix33 result;

		result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2];
		result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1] + m[2][1] * mx.m[0][2];
		result.m[0][2] = m[0][2] * mx.m[0][0] + m[1][2] * mx.m[0][1] + m[2][2] * mx.m[0][2]; 
		result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1] + m[2][0] * mx.m[1][2];
		result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1] + m[2][1] * mx.m[1][2];
		result.m[1][2] = m[0][2] * mx.m[1][0] + m[1][2] * mx.m[1][1] + m[2][2] * mx.m[1][2]; 
		result.m[2][0] = m[0][0] * mx.m[2][0] + m[1][0] * mx.m[2][1] + m[2][0] * mx.m[2][2]; 
		result.m[2][1] = m[0][1] * mx.m[2][0] + m[1][1] * mx.m[2][1] + m[2][1] * mx.m[2][2]; 
		result.m[2][2] = m[0][2] * mx.m[2][0] + m[1][2] * mx.m[2][1] + m[2][2] * mx.m[2][2];

		return result;
	}

	friend vector2 operator * (const vector2& v, const matrix33 mx) {
		vector2 result;

		result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
		result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

		return result;
	}

public:
	float m[3][3];
};