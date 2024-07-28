#pragma once

#include "map"
#include "Patch.h"
#include "DetourManager.h"
#include <string>


class MemoryController
{
public:
	static std::map<std::string, Patch*> PatcherController;
	static std::map<std::string, DetourManager*> DetourPatcher;
	static int SearchLength;

	static DetourManager* CheckDetours(DWORD Address);
	static Patch* CheckPatchs(DWORD Address);
	static bool		      BeforeOrAfter(DWORD Address, DWORD Address2);


};
