#pragma once

enum WardenEnum
{
	ModuleHandle = 0x4,
	AddTwoNumbers = 0x08,
	MemoryCheck = 0x0C,
	ModuleCheck = 0x10,
	CallProcCheckHashAndCompare = 0x1C,
	DriverCheck = 0x20,
	TimingCheck = 0x24,
	GetTickCounterFromMemory = 0x28,
	HeapFreeEx = 0x50,
	Return0 = 0xDC,
	ProcAddress = 0x18,
	GetMethod = 0xE8,
	CheckStructValue = 0x1FC,
	FreeHeap = 0x2C,
	_CloseHandle = 0xF0,
	CheckFunctions = 0x00,
	ReturnControl = 0x200,
	_DuplicateHandle = 0x100,
	PageStoreInfo = 0x7B8
};
