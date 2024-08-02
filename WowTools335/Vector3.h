#pragma once
#include <array>
#include <string>

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const float* floatArray);
	bool Invalid() const;
	std::array<float, 3> ToFloatArray() const;
	float DistanceTo(const Vector3& loc) const;
	float Distance2D(const Vector3& loc) const;
	float Length() const;
	std::string ToJson() const;
	Vector3 operator-(Vector3& other);
	Vector3& operator=(const Vector3& v);
	Vector3 operator*(float scalar);
	Vector3 operator-(const Vector3& other);
	// Custom addition operator
	Vector3 operator+(const Vector3& other);
	Vector3 Normalize() const;
	Vector3 Normalize(Vector3 const& v) const;
};