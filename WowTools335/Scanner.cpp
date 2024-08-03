#include "Scanner.h"

PVOID Scanner::FindPattern(PVOID pMemBase, DWORD dwSize, pTPattern pPattern)
{
	DWORD dwRemain = dwSize;
	PBYTE pMem = (PBYTE)pMemBase, pMemCmp;
	BOOL fFound = false;

	while (dwRemain >= pPattern->dwSequenceLen)
	{
		PBYTE pBytesToCompare = pPattern->pByteSequence;
		pMemCmp = pMem;

		for (DWORD i = 0; pPattern->pPatternString[i]; i++)
		{
			bool skip = false;
			DWORD len = 0;
			switch (pPattern->pPatternString[i])
			{
			case '?':
				skip = true;
			case 'x':
				i++;
				len = atoi(pPattern->pPatternString + i);
			}
			if (len)
			{
				if (!skip)
					fFound = !memcmp(pMemCmp, pBytesToCompare, len);

				pBytesToCompare += len;
				pMemCmp += len;
			}
			if (!fFound) break;
		}
		if (fFound) return pMem;

		pMem++;
		dwRemain--;
	}
	return 0;
}
PVOID Scanner::ScanMem(pTPattern pPattern)
{
	DWORD dwBase = 0x10000, dwProcessing;
	MEMORY_BASIC_INFORMATION Mem;
	PVOID pResult = 0;

	do {
		if (dwProcessing = VirtualQuery((PVOID)dwBase, &Mem, sizeof(MEMORY_BASIC_INFORMATION)))
		{

			if (Mem.State == MEM_COMMIT && Mem.Protect <= 0x80 && Mem.Protect >= 0x20)
			{
				pResult = FindPattern(Mem.BaseAddress, Mem.RegionSize, pPattern);
			}
			dwBase = Mem.RegionSize + (DWORD)Mem.BaseAddress;
		}
	} while (dwProcessing && dwBase < 0x7C900000 && (!pResult || pResult == pPattern->pByteSequence));

	return pResult;
}
std::vector<PVOID> Scanner::ScanMemList(pTPattern pPattern)
{
	DWORD dwBase = 0x10000, dwProcessing;
	MEMORY_BASIC_INFORMATION Mem;
	std::vector<PVOID> results; // Store multiple results in a vector

	do {
		if (dwProcessing = VirtualQuery((PVOID)dwBase, &Mem, sizeof(MEMORY_BASIC_INFORMATION)))
		{
			if (Mem.State == MEM_COMMIT && Mem.Protect <= 0x80 && Mem.Protect >= 0x20)
			{
				PVOID pResult = FindPattern(Mem.BaseAddress, Mem.RegionSize, pPattern);
				if (pResult)
				{
					results.push_back(pResult); // Store the result in the vector
				}
			}
			dwBase = (DWORD)Mem.BaseAddress + Mem.RegionSize;
		}
	} while (dwProcessing && dwBase < 0x7C900000);

	return results;
}


bool IsDynamicMemory(const MEMORY_BASIC_INFORMATION& memInfo) {
	return memInfo.State == MEM_COMMIT &&
		(memInfo.Protect == PAGE_READWRITE || memInfo.Protect == PAGE_WRITECOPY ||
			memInfo.Protect == PAGE_EXECUTE_READWRITE || memInfo.Protect == PAGE_EXECUTE_WRITECOPY);
}

// Function to find a pattern in memory and check if the address is in dynamic memory
PVOID Scanner::FindPatternAddress(const BYTE* pattern, DWORD patternSize) {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	PVOID targetAddress = nullptr;

	for (PBYTE currentAddress = static_cast<PBYTE>(sysInfo.lpMinimumApplicationAddress);
		currentAddress < static_cast<PBYTE>(sysInfo.lpMaximumApplicationAddress);) {
		MEMORY_BASIC_INFORMATION memInfo;
		if (VirtualQuery(currentAddress, &memInfo, sizeof(memInfo)) != 0) {
			if (IsDynamicMemory(memInfo))
			{
				PBYTE buffer = new BYTE[memInfo.RegionSize];
				SIZE_T bytesRead;
				if (ReadProcessMemory(GetCurrentProcess(), currentAddress, buffer, memInfo.RegionSize, &bytesRead)) {
					for (DWORD offset = 0; offset <= memInfo.RegionSize - patternSize; ++offset) {
						if (memcmp(buffer + offset, pattern, patternSize) == 0) {
							targetAddress = currentAddress + offset;
							break;
						}
					}
				}
				delete[] buffer;
			}
			if (targetAddress) {
				break; // Pattern found, no need to continue searching
			}
			currentAddress += memInfo.RegionSize;
		}
		else {
			break;
		}
	}

	return targetAddress;
}