#include "DetourManager.h"
#include <detours.h>
#include <iostream>

DetourManager::DetourManager(DWORD address, PVOID* targetAddress, PVOID funcAddress)
{

    this->TargetAddress = targetAddress;
    this->Address = address;
    this->FuncAddress = funcAddress;
    this->isApplied = false;

    Apply();

}

bool DetourManager::Apply()
{
    if (!isApplied)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(TargetAddress, FuncAddress);
        LONG error = DetourTransactionCommit();
        isApplied = (error == NO_ERROR);
    }
    return isApplied;
}

bool DetourManager::Remove()
{
    if (isApplied)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(TargetAddress, FuncAddress);
        LONG error = DetourTransactionCommit();
        isApplied = !(error == NO_ERROR);
    }
    return !isApplied;
}