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
			printf("WardenDataHandler > WardenStructure >  0x%x\n", WardenStructure);
			if (WardenStructure != NULL)
			{
				DWORD WardenVtableptr = _ReadDWORD(WardenStructure + 0x228);
				printf("WardenDataHandler > WardenVtableptr >  0x%x\n", WardenVtableptr);
				if (WardenVtableptr != NULL || WardenVtableptr >  0x1000000)
				{
					DWORD WardenVtable = _ReadDWORD(WardenVtableptr);
					printf("WardenDataHandler > WardenVtable >  0x%x\n", WardenVtable);
					if (WardenVtable == NULL)
					{
						printf("yo its fucking zero bro\n\n");
						Warden::Clear();
						return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);

					}
					
					if (WardenVtable != NULL && OldAddress != WardenVtable)
					{
						printf("your good bruh\n\n");
						OldAddress = WardenVtable;
						Warden::Hooks(WardenStructure, WardenVtable);
					}
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
