#include "MemoryController.h"
#include <Windows.h>


std::map<std::string, Patch*> MemoryController::PatcherController;
std::map<std::string, DetourManager*> MemoryController::DetourPatcher;
int MemoryController::SearchLength = 100;

Patch* MemoryController::CheckPatchs(DWORD Address)
{

	for (const auto& obj : PatcherController)
	{
		DWORD Addr = (DWORD)obj.second->_Address;
		if (Addr == Address || BeforeOrAfter(Address, Addr))
		{
			if (!obj.second->IsModified)
				continue;

			printf("[Warden] Patch Warden Scanning %s\n", obj.first.c_str());
			return obj.second;
		}
	}
	return nullptr;
}


bool MemoryController::BeforeOrAfter(DWORD Address, DWORD Address2)
{
	int index = 0;
	for (DWORD addr = Address; addr > Address - SearchLength; --addr)
	{
		if (addr == Address2)
		{
			printf("[Warden] Patch found within %d bytes before Address.\n", index);
			return true;
		}
		index++;
	}
	int index2 = 0;
	for (DWORD addr = Address; addr < Address + SearchLength; ++addr)
	{
		if (addr == Address2)
		{
			printf("[Warden] Patch found at %d bytes after Address.\n", index2);
			return true;
		}
		index2++;
	}
	return false;
}


DetourManager* MemoryController::CheckDetours(DWORD Address)
{

	for (const auto& obj : DetourPatcher)
	{
		DWORD Addr = (DWORD)obj.second->Address;

		if (Addr == Address || BeforeOrAfter(Address, Addr))
		{
			printf("[Warden] Detour Warden Scanning %s\n", obj.first.c_str());
			return obj.second;
		}
	}
	return nullptr;
}
