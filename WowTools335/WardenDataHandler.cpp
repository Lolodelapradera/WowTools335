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
			DWORD WardenStructure = _ReadDWORD(0x00D31A4C);
			//printf("WardenDataHandler > WardenStructure >  0x%x\n", WardenStructure);
			if (WardenStructure != NULL)
			{
				DWORD WardenVtableptr = _ReadDWORD(WardenStructure + 0x228);
				//printf("WardenDtataHandler > WardenVtableptr >  0x%x\n", WardenVtableptr);
				if (WardenVtableptr != NULL)
				{
					DWORD WardenVtable = _ReadDWORD(WardenVtableptr);
					//printf("WardenDataHandler > WardenVtable >  0x%x\n", WardenVtable);
					if (WardenVtable != NULL)
					{
						if (WardenStructOld == NULL)
						{
							Warden::ApplyHooks(WardenStructure, WardenVtable);
							WardenStructOld = WardenStructure;
							WardenVtablePtrOld = WardenVtableptr;
							WardenVtableOld = WardenVtable;
						}
						else if (WardenStructOld != WardenStructure || WardenVtablePtrOld != WardenVtableptr || WardenVtableOld != WardenVtable)
						{
							Warden::RemoveHooks();
							Warden::ApplyHooks(WardenStructure, WardenVtable);
							WardenStructOld = WardenStructure;
							WardenVtablePtrOld = WardenVtableptr;
							WardenVtableOld = WardenVtable;
						}
					}
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
