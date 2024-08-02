#pragma once

#include "Helperfunctions.h"
#include <filesystem>
#include "Vector3.h"


inline int PerformanceCount() { return ((int(__cdecl*)())0x0086AE20)(); }

double RoundNumber(double f)
{
	return std::round(f * 10.0) / 10.0;
}

std::string tohex16(UINT64 i)
{
	std::stringstream stream;
	stream << "0x" << std::setw(16) << std::setfill('0') << std::hex << std::uppercase << i;
	std::string result = stream.str();
	return result;
}

float NormalizeRadian(float radian) //ClampAngle
{
	while (radian < 0)
	{
		radian = radian + 2 * PI;
	}
	while (radian >= 2 * PI)
	{
		radian = radian - 2 * PI;
	}
	return radian;
}

float CalculateFacingAngle(Vector3 start, Vector3 end)
{
	return atan2((end.Y - start.Y), (end.X - start.X));
}
