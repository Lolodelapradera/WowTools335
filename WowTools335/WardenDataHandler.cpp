#include "Warden.h"
#include "WardenHelpers.h"

DWORD OldAddress = 0;
Warden::WardenDataHandlerType Warden::OriginalWardenDataHandler = (Warden::WardenDataHandlerType)0x007DA850;
int __cdecl Warden::WardenDataHandler(int a1, uint16_t opcode, int a3, int pDataStore)
{
	if (opcode == 0x2E6)
	{
		if (*(DWORD*)0x00D31A48 != 0)
		{
			DWORD WardenStructure = _ReadDWORD(0x00D31A4C);
			if (WardenStructure != 0)
			{
				DWORD WardenVtable = _ReadDWORD(_ReadDWORD(WardenStructure + 0x228));

				if (WardenVtable != 0 && OldAddress != WardenVtable)
				{
					OldAddress = WardenVtable;
					Warden::Clear();
					Warden::Hooks(WardenStructure, WardenVtable);
					IsApplied = true;
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
