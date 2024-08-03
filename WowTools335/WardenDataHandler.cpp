#include "Warden.h"
#include "WardenHelpers.h"

DWORD OldAddress = -1;
DWORD load = 0;
Warden::WardenDataHandlerType Warden::OriginalWardenDataHandler = (Warden::WardenDataHandlerType)0x007DA850;
int __cdecl Warden::WardenDataHandler(int a1, uint16_t opcode, int a3, int pDataStore)
{
	if (opcode == 0x2E6)
	{
		if (_ReadDWORD(0x00D31A48) != NULL)
		{
			DWORD WardenStructure = _ReadDWORD(0x00D31A4C);
			if (WardenStructure != NULL)
			{
				DWORD WardenVtableptr = _ReadDWORD(WardenStructure + 0x228);
				
				if (WardenVtableptr != NULL)
				{
					DWORD WardenVtable = _ReadDWORD(WardenVtableptr);

					if (WardenVtable != NULL && OldAddress != WardenVtable)
					{
						OldAddress = WardenVtable;
						Warden::Clear();
						Warden::Hooks(WardenStructure, WardenVtable);
						IsApplied = true;
					}
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
