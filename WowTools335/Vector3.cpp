#pragma once
#include "Vector3.h"

Vector3::Vector3()
{
	X = 0;
	Y = 0;
	Z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3::Vector3(const float* floatArray)
{
	this->X = floatArray[0];
	this->Y = floatArray[1];
	this->Z = floatArray[2];
}

bool Vector3::Invalid() const
{
	return (this->X == 0 && this->Y == 0 && this->Z == 0);
}

std::array<float, 3> Vector3::ToFloatArray() const
{
	return { this->X, this->Y, this->Z };
}

float Vector3::DistanceTo(const Vector3& loc)  const
{
	return sqrt(pow(X - loc.X, 2) + pow(Y - loc.Y, 2) + pow(Z - loc.Z, 2));
}

float Vector3::Distance2D(const Vector3& loc)  const
{
	return sqrt(pow(X - loc.X, 2) + pow(Y - loc.Y, 2));
}

float Vector3::Length() const
{
	return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
}

std::string Vector3::ToJson()  const
{
	return "{ \"X\": " + std::to_string(X) + ", \"Y\": " + std::to_string(Y) + ", \"Z\": " + std::to_string(Z) + "}";
}

Vector3 Vector3::operator-(Vector3& other) {
	return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3& Vector3::operator=(const Vector3& v) {
	X = v.X;
	Y = v.Y;
	Z = v.Z;
	return *this;
}

Vector3 Vector3::operator*(float scalar) {
	return Vector3(X * scalar, Y * scalar, Z * scalar);
}

Vector3 Vector3::operator-(const Vector3& other) {
	return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

// Custom addition operator
Vector3 Vector3::operator+(const Vector3& other) {
	return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3 Vector3::Normalize()  const {
	float length = sqrt(X * X + Y * Y + Z * Z);
	return Vector3(X / length, Y / length, Z / length);
}

inline Vector3 Vector3::Normalize(Vector3 const& v)  const
{
	Vector3 vec;
	float length = v.Length();
	if (length != 0)
	{
		vec.X = v.X / length;
		vec.Y = v.Y / length;
		vec.Z = v.Z / length;
	}
	return vec;
}
