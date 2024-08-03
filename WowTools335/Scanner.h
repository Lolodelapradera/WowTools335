#pragma once
#include <minwindef.h>
#include <stdlib.h>
#include <vector>

namespace Scanner
{
	typedef class _Pattern
	{
	public:
		PBYTE pByteSequence;
		DWORD dwSequenceLen;
		PCHAR pPatternString;

		_Pattern(PCHAR b, DWORD l, PCHAR p) {
			pByteSequence = (PBYTE)b;
			dwSequenceLen = l;
			pPatternString = p;
		};
		_Pattern(PCHAR b, PCHAR p) {
			pByteSequence = (PBYTE)b;
			dwSequenceLen = 0;
			pPatternString = p;

			// calc actual lenght
			for (DWORD i = 0; pPatternString[i]; i++)
			{
				DWORD len = 0;
				switch (pPatternString[i])
				{
				case 'x':
				case '?':
					i++;
					len = atoi(pPatternString + i);
				}
				dwSequenceLen += len;
			}
		};
	} *pTPattern, TPattern; 

	PVOID	ScanMem(pTPattern pszPattern);
	PVOID	FindPattern(PVOID pMemBase, DWORD dwSize, pTPattern pPattern);
	PVOID   FindPatternAddress(const BYTE* pattern, DWORD patternSize);
	std::vector<PVOID> ScanMemList(pTPattern pPattern);
	std::vector<PVOID> FindPatternAddresses(const BYTE* pattern, DWORD patternSize);
}