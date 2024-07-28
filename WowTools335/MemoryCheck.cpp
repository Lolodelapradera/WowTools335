#include "Warden.h"
#include "WardenHelpers.h"


Warden::_MemoryCheck Warden::OrignalMemoryCheck = nullptr;
CRITICAL_SECTION g_criticalSection;
int __stdcall Warden::MemoryCheck(int buffer, int handle, int address, int length)
{
    /* printf("[Warden] MemCheck : Address = 0x%x size = %d\n", address, length);*/
    Loggin(true, "Warden_Scans.txt", "[Warden] MemCheck : Address = 0x%x size = %d\n", address, length);

    auto detour = MemoryController::CheckDetours(address);
    auto patch = MemoryController::CheckPatchs(address);

    if (detour != nullptr || patch != nullptr)
    {
        InitializeCriticalSection(&g_criticalSection);
        EnterCriticalSection(&g_criticalSection);

        if (detour != nullptr)
        {
            // Remove the detour temporarily, call the original function, and reapply the detour
            detour->Remove();
            int result = OrignalMemoryCheck(buffer, handle, address, length);
            detour->Apply();
            LeaveCriticalSection(&g_criticalSection);
            return result;
        }

        if (patch != nullptr)
        {
            // Restore the patch temporarily, call the original function, and reapply the patch
            patch->Restore();
            int result = OrignalMemoryCheck(buffer, handle, address, length);
            patch->Apply();
            LeaveCriticalSection(&g_criticalSection);
            return result;
        }

        LeaveCriticalSection(&g_criticalSection);
    }

    return OrignalMemoryCheck(buffer, handle, address, length);
}