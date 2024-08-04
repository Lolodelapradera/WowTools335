#include "Warden.h"
#include "WardenHelpers.h"

DWORD WardenStructOld = NULL;
DWORD WardenVtablePtrOld = NULL;
DWORD WardenVtableOld = NULL;
Warden::WardenDataHandlerType Warden::OriginalWardenDataHandler = (Warden::WardenDataHandlerType)0x007DA850;
int __cdecl Warden::WardenDataHandler(int a1, uint16_t opcode, int a3, int pDataStore)
{
	if (opcode == 0x2E6)
	{
		if (_ReadDWORD(0x00D31A48) != NULL)
		{
			DWORD WardenStruct = _ReadDWORD(0x00D31A4C);
			if (WardenStruct != NULL)
			{
				DWORD WardenVtablePtr = _ReadDWORD(WardenStruct + 0x228);
				if (WardenVtablePtr != NULL)
				{
					DWORD WardenVtable = _ReadDWORD(WardenVtablePtr);
					if (WardenVtable != NULL)
					{
						if (WardenStructOld == NULL)
						{
							Warden::ApplyHooks(WardenStruct, WardenVtable);
							WardenStructOld = WardenStruct;
							WardenVtablePtrOld = WardenVtablePtr;
							WardenVtableOld = WardenVtable;
						}
						else if (WardenStructOld != WardenStruct || WardenVtablePtrOld != WardenVtablePtr || WardenVtableOld != WardenVtable)
						{
							Warden::RemoveHooks();
							Warden::ApplyHooks(WardenStruct, WardenVtable);
							WardenStructOld = WardenStruct;
							WardenVtablePtrOld = WardenVtablePtr;
							WardenVtableOld = WardenVtable;
						}
					}
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
