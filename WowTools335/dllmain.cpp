// dllmain.cpp : Defines the entry point for the DLL application.
#include "SourceHeader.h"

BOOL APIENTRY DllMain(HMODULE instance, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
   
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainController, NULL, 0, NULL);
        break;

    case DLL_PROCESS_DETACH:
        MemoryClean();
        break;
    }
    return TRUE;
}

