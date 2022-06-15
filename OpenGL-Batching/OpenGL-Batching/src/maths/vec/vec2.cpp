#include "vec2.h"

vec2::vec2()
	:x(0.0f), y(0.0f)
{
}

vec2::vec2(float x, float y)
	:x(x), y(y)
{
}

float vec2::getLength()
{
	return sqrt(x * x + y * y);
}

vec2 vec2::getNormalVector()
{
	vec2 normalVec;
	normalVec.x = x / getLength();
	normalVec.y = y / getLength();
	return normalVec;
}

vec2 vec2::normalize()
{
	float length = getLength();
	x = x / length;
	y = y / length;

	return *this;
}

// Vector arithmetic
vec2 vec2::operator+(const vec2& vec)
{
	return vec2((x + vec.x), (y + vec.y));

}

vec2 vec2::operator-(const vec2& vec)
{
	return vec2((x - vec.x), (y - vec.y));

}
vec2 vec2::operator*(const vec2& vec)
{
	return vec2((x * vec.x), (y * vec.y));

}
vec2 vec2::operator*(const float& scalar)
{
	return vec2((x * scalar), (y * scalar));

}
vec2 vec2::operator/(const vec2& vec)
{
	return vec2((x / vec.x), (y / vec.y));

}
vec2 vec2::operator/(const float& scalar)
{
	return vec2((x / scalar), (y / scalar));

}

// Advanced vector arithmetic // dot product, corss prodcut
float vec2::dot(const vec2& vec)
{
	return (x * vec.x + y * vec.y);
}

// Vector comparison
bool vec2::operator==(const vec2& vec)
{
	if (x == vec.x && y == vec.y)
	{
		return true;
	}
	return false;
}

bool vec2::operator!=(const vec2& vec)
{
	if (x == vec.x && y == vec.y)
	{
		return false;
	}
	return true;
}
std::ostream& operator<<(std::ostream& stream, const vec2& vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
