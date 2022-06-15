#pragma once

#include <iostream>
#include <cmath>

#include "maths/vec/vec3.h"
#include "maths/vec/vec4.h"


struct mat4
{
	float mat4x4[4][4];

	mat4(float diagonal = 1.0f);
	void makeNull();
	void makeIdentity();
	
	float* operator[](int index);

};

// Transformation matrices
struct scale : public mat4
{
	scale(const vec3& sc);

};
struct translate : public mat4

{
	translate(const vec3& tr);
};
struct rotate : public mat4
{
	rotate(float angle, const vec3& rot);
};

// Pojection matrices
struct orthographic :public mat4
{
	orthographic(float left, float right, float top, float bottom, float znear, float zfar);
};

// Matrix - Vector multiplication
vec4 operator*(const mat4& mat, const vec4& vec);

// Matrix - Matrix multiplication
mat4 operator* (const mat4& mat1, const mat4& mat2);

std::ostream& operator<<(std::ostream& stream, const mat4& mat);
	

