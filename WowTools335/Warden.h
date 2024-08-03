#pragma once
#include <Windows.h>
#include "MemoryController.h"
#include <cstdint>

class Warden
{
public:
	static void Initiative();
	static void Dispose();
	static void Clear();
	static void ReapplyHacks();
	static void Hooks(DWORD Structure, DWORD Vtable);


#pragma region WardenData

	static int __cdecl WardenDataHandler(int a1, uint16_t opcode, int a3, int pDataStore);
	typedef int(__cdecl* WardenDataHandlerType)(int a1, uint16_t opcode, int a3, int pDataStore);
	static WardenDataHandlerType OriginalWardenDataHandler;


#pragma endregion

#pragma region  WardenMethods

#pragma region MemoryCheck
	static int __stdcall MemoryCheck(int a1, int a2, int a3, int a4);
	typedef int(__stdcall* _MemoryCheck)(int a1, int a2, int a3, int a4);
	static _MemoryCheck OrignalMemoryCheck;
#pragma endregion
#pragma region PageScan
	static int  __fastcall PageCheck(DWORD* p_this, int EDX, bool isCheckB, DWORD* p_hash, DWORD* p_seed, int Offset, int length);
	typedef  int(__thiscall* PageCheckOriginal)(DWORD* p_this, bool isCheckB, DWORD* p_hash, DWORD* p_seed, int address, int length);
	static PageCheckOriginal pPageCheckOriginal;
#pragma endregion
#pragma region DriverCheck
	static bool __fastcall DriverCheck(BYTE* a1, LPCSTR lpDeviceName, const void* p_hash, const void* p_seed);
	typedef bool(__thiscall* DriverCheckType)(BYTE*, LPCSTR, const void*, const void*);
	static DriverCheckType OriginalDriverCheck;
#pragma endregion
#pragma region LuaStrCheck
	static int __cdecl Lua_String_Check(const char* str, int a2, int a3);
	using LuaExecute = int(__cdecl*)(const char*, int, int);
	static LuaExecute OrignalLua_String_Check;
#pragma endregion
#pragma region ModuleCheck
	static int __fastcall Warden_ModuleCheck(DWORD* p_this, DWORD* a2, DWORD* a3);
	typedef int(__thiscall* _ModuleCheck)(DWORD* p_this, DWORD* a2, DWORD* a3);
	static _ModuleCheck OriginalModuleCheck;

#pragma endregion


#pragma region ShutDownAndUnload

	//static int  ShutdownAndUnload();
	//typedef int(ShutdownAndUnloadtype)();
	//static ShutdownAndUnloadtype OriginalShutdownAndUnload;

	static int ShutdownAndUnload(); // Custom method
	typedef int(*ShutdownAndUnloadtype)(); // Typedef for the original method
	static ShutdownAndUnloadtype OriginalShutdownAndUnload;
	//0x08dA420
#pragma endregion


#pragma endregion

#pragma region  Variables
	static bool IsApplied;
	static DWORD WoWBase;
#pragma endregion

};
