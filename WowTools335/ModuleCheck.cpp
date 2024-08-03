#include "Warden.h"
#include <iostream>
#include "MemoryController.h"
#include "WardenHelpers.h"


Warden::_ModuleCheck Warden::OriginalModuleCheck = nullptr;
int __fastcall Warden::Warden_ModuleCheck(DWORD* p_this, DWORD* a2, DWORD* a3)
{


	//std::cout << ParseSha1Hash(a2, a3).c_str() << std::endl;
	return OriginalModuleCheck(p_this, a2, a3);;
}