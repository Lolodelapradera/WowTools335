#pragma once
#include "Windows.h"

class DetourManager
{
public:
	DetourManager(DWORD Address, PVOID* targetAddress, PVOID funcAddress);

	bool Apply();
	bool Remove();
	DWORD   Address;
	PVOID* TargetAddress;
	PVOID   FuncAddress;
	bool    isApplied;
};

