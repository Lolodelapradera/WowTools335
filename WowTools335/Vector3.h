#pragma once
#include <array>
#include <string>

class Vector
{
public:
	float X;
	float Y;
	float Z;
	Vector();
	Vector(float x, float y, float z);
	Vector(const float* floatArray);
	bool Invalid() const;
	std::array<float, 3> ToFloatArray() const;
	float DistanceTo(const Vector& loc) const;
	float Distance2D(const Vector& loc) const;
	float Length() const;
	std::string ToJson() const;
	Vector operator-(Vector& other);
	Vector& operator=(const Vector& v);
	Vector operator*(float scalar);
	Vector operator-(const Vector& other);
	// Custom addition operator
	Vector operator+(const Vector& other);
	Vector Normalize() const;
	Vector Normalize(Vector const& v) const;
};