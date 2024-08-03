#include "Warden.h"
#include "WardenHelpers.h"
#include "Scanner.h"

BYTE pattern[] = { 0xAC, 0x29, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00 };
DWORD OldAddress = -1;
DWORD load = 0;
Warden::WardenDataHandlerType Warden::OriginalWardenDataHandler = (Warden::WardenDataHandlerType)0x007DA850;
int __cdecl Warden::WardenDataHandler(int a1, uint16_t opcode, int a3, int pDataStore)
{
	if (opcode == 0x2E6)
	{
		if (_ReadDWORD(0x00D31A48) != NULL)
		{
			
			//Scanner::TPattern Pattern("\xAC\x29\xAF\x00\x00\x00\x00\x00", "x8");  //8B ?? B0 07 00 00
			//DWORD Wardenbase = (DWORD)Scanner::ScanMem(&Pattern);
			//DWORD Wardenbase = (DWORD)Scanner::ScanMem("\xAC\x29\xAF\x00\x00\x00\x00\x00", "");
			//printf("WardenDataHandler > WardenStructure  >  0x%x\n", Wardenbase);

			DWORD WardenStructure = _ReadDWORD(0x00D31A4C);
			//printf("WardenDataHandler > WardenStructure >  0x%x\n", WardenStructure);
			if (WardenStructure != NULL)
			{
				DWORD WardenVtableptr = _ReadDWORD(WardenStructure + 0x228);
				//printf("WardenDataHandler > WardenVtableptr >  0x%x\n", WardenVtableptr);
				if (WardenVtableptr != NULL)
				{
					DWORD WardenVtable = _ReadDWORD(WardenVtableptr);
					//printf("WardenDataHandler > WardenVtable >  0x%x\n", WardenVtable);
					if (WardenVtable == NULL)
					{
						//printf("yo its fucking zero bro\n\n");
						Warden::Clear();
						OldAddress = -1;
						return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);

					}
					
					if (WardenVtable != NULL && OldAddress != WardenVtable)
					{
						//printf("your good bruh\n\n");
						OldAddress = WardenVtable;
						Warden::Clear();
						Warden::Hooks(WardenStructure, WardenVtable);
					}
				}
			}
		}
	}
	return OriginalWardenDataHandler(a1, opcode, a3, pDataStore);
}
