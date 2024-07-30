#pragma once
#include "Vector3.h"

Vector::Vector()
{
	X = 0;
	Y = 0;
	Z = 0;
}

Vector::Vector(float x, float y, float z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector::Vector(const float* floatArray)
{
	this->X = floatArray[0];
	this->Y = floatArray[1];
	this->Z = floatArray[2];
}

bool Vector::Invalid() const
{
	return (this->X == 0 && this->Y == 0 && this->Z == 0);
}

std::array<float, 3> Vector::ToFloatArray() const
{
	return { this->X, this->Y, this->Z };
}

float Vector::DistanceTo(const Vector& loc)  const
{
	return sqrt(pow(X - loc.X, 2) + pow(Y - loc.Y, 2) + pow(Z - loc.Z, 2));
}

float Vector::Distance2D(const Vector& loc)  const
{
	return sqrt(pow(X - loc.X, 2) + pow(Y - loc.Y, 2));
}

float Vector::Length() const
{
	return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
}

std::string Vector::ToJson()  const
{
	return "{ \"X\": " + std::to_string(X) + ", \"Y\": " + std::to_string(Y) + ", \"Z\": " + std::to_string(Z) + "}";
}

Vector Vector::operator-(Vector& other) {
	return Vector(X - other.X, Y - other.Y, Z - other.Z);
}

Vector& Vector::operator=(const Vector& v) {
	X = v.X;
	Y = v.Y;
	Z = v.Z;
	return *this;
}

Vector Vector::operator*(float scalar) {
	return Vector(X * scalar, Y * scalar, Z * scalar);
}

Vector Vector::operator-(const Vector& other) {
	return Vector(X - other.X, Y - other.Y, Z - other.Z);
}

// Custom addition operator
Vector Vector::operator+(const Vector& other) {
	return Vector(X + other.X, Y + other.Y, Z + other.Z);
}

Vector Vector::Normalize()  const {
	float length = sqrt(X * X + Y * Y + Z * Z);
	return Vector(X / length, Y / length, Z / length);
}

inline Vector Vector::Normalize(Vector const& v)  const
{
	Vector vec;
	float length = v.Length();
	if (length != 0)
	{
		vec.X = v.X / length;
		vec.Y = v.Y / length;
		vec.Z = v.Z / length;
	}
	return vec;
}
