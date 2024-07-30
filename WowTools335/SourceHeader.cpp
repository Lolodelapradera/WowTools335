#include "SourceHeader.h"
#include "Warden.h"
#include "Hook.h"


void PatchInvaildPointers()
{
	*(int*)0x00D415B8 = 1;
	*(int*)0x00D415BC = 0x7FFFFFFF;
}

void ConsoleApp()
{
	AllocConsole();

	FILE* stream;

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONOUT$", "w", stdout);
}


DWORD MemoryClean()
{
	Warden::Dispose();
	Hook::UnHookDirectX();
	FreeConsole();
	return 0;
}


void LoadHacks()
{
	MemoryController::PatcherController["AntiAfk"] = new Patch(0x052B25F, { 0xE9, 0xEE, 0xFD, 0xFF, 0xFF, 0x90 });
	MemoryController::PatcherController["WaterWalking"] = new Patch(0x0075E439, { 0x75, 0x14, 0x81, 0xCF });
	MemoryController::PatcherController["LuaUnlocker"] = new Patch(0x005191E0, { 0xEB, 0x57, 0x00, 0x00 });
	MemoryController::PatcherController["WallClimb"] = new Patch(0x00A37F0C, { 0x00, 0x00, 0x00, 0x00 });
	MemoryController::PatcherController["M2Collision"] = new Patch(0x007A52EC, { 0x75 });
	MemoryController::PatcherController["LanguagePatch"] = new Patch(0x0050599F, { 0x90, 0x90, 0x8B, 0x55 });
	MemoryController::PatcherController["AVRPatch"] = new Patch(0x00510089, { 0x90, 0x90 });
}

DWORD MainController()
{
	LoadHacks();
	Warden::Initiative();
	Hook::HookDirectX();
	ConsoleApp();
	Warden::Initiative();
	PatchInvaildPointers();
	Lua_OpenFrameHook();

	return 0;
}