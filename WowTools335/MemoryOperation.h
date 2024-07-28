#pragma once
#include <vector>
#include "Windows.h"

typedef unsigned char byte;

class MemoryOperation
{


public:
	std::vector<byte> original_bytes{};
	std::vector<byte> new_bytes{};
	byte* target{};

	MemoryOperation(byte* target_arg) :target{ target_arg } {}
	MemoryOperation(byte* target_arg, std::initializer_list<byte> bytes)
		: target{ target_arg }
		, new_bytes{ bytes }
	{}

	virtual ~MemoryOperation() {}
	virtual void Apply() = 0;
	virtual void Restore() = 0;
	bool IsModified = false;
	DWORD _Address = 0;
};

