#include "Warden.h"
#include <iostream>
#include "MemoryController.h"
#include "WardenHelpers.h"

Warden::PageCheckOriginal Warden::pPageCheckOriginal = nullptr;
int  __fastcall Warden::PageCheck(DWORD* p_this, int EDX, bool isCheckB, DWORD* p_hash, DWORD* p_seed, int Offset, int length)
{

    DWORD address = (WoWBase + Offset);
    auto detour = MemoryController::CheckDetours(address);
    auto patch = MemoryController::CheckPatchs(address);

    if (detour != nullptr || patch != nullptr)
    {
        CRITICAL_SECTION CriticalSection;
        InitializeCriticalSection(&CriticalSection);
        EnterCriticalSection(&CriticalSection);
        if (detour != nullptr)
        {
            // Remove the detour temporarily, call the original function, and reapply the detour
            detour->Remove();
            int result = pPageCheckOriginal(p_this, isCheckB, p_hash, p_seed, Offset, length);
            detour->Apply();
            LeaveCriticalSection(&CriticalSection);
            return result;
        }

        if (patch != nullptr)
        {
            // Restore the patch temporarily, call the original function, and reapply the patch
            patch->Restore();
            int result = pPageCheckOriginal(p_this, isCheckB, p_hash, p_seed, Offset, length);
            patch->Apply();
            LeaveCriticalSection(&CriticalSection);
            return result;
        }

        LeaveCriticalSection(&CriticalSection);
    }

    Loggin(true, "Warden_Scans.txt", "[Warden] PAGE_CHECK_%s : Address = 0x%X Length = %d Hash = %s\n", (isCheckB ? "B" : "A"), address, length, ParseSha1Hash(p_seed, p_hash).c_str());
    /*  printf("[Warden] PAGE_CHECK_%s : Address = 0x%X Length = %d Hash = %s\n", (isCheckB ? "B" : "A"), address, length, ParseSha1Hash(p_seed, p_hash).c_str());*/

    return pPageCheckOriginal(p_this, isCheckB, p_hash, p_seed, Offset, length);
}