#pragma once

#include "SharedHeaders.h"

std::string tohex16(UINT64 i);
const float PI{ 3.141592653589793f };
double RoundNumber(double f);
inline int PerformanceCount();

float NormalizeRadian(float radian);
float CalculateFacingAngle(Vector3 start, Vector3 end);
