#include "Warden.h"
#include "WardenHelpers.h"
#include "WardenEnums.h"

bool Warden::IsApplied = false;
DWORD Warden::WoWBase = 0;
void Warden::Initiative()
{
    WoWBase = GetBaseAddress();
    MemoryController::DetourPatcher["Warden_Handler"] = new DetourManager(0x007DA850, &(PVOID&)OriginalWardenDataHandler, Warden::WardenDataHandler);
    MemoryController::DetourPatcher["Warden_ShutdownAndUnload"] = new DetourManager(0x08dA420, &(PVOID&)OriginalShutdownAndUnload, Warden::ShutdownAndUnload);
}

void Warden::Dispose()
{
    Clear();
    MemoryController::DetourPatcher["Warden_Handler"]->Remove();
}

std::vector<std::string> Loadedhacks;

void Warden::Clear()
{
    if (!IsApplied)
        return;

    if (!MemoryController::PatcherController.empty())
    {
        for (const auto& key : MemoryController::PatcherController)
        {
            if (!key.second->IsModified)
                continue;

            Loadedhacks.push_back(key.first);
            key.second->Restore();
        }
  }


  /*  MemoryController::PatcherController["AntiAfk"]->Restore();
    MemoryController::PatcherController["WaterWalking"]->Restore();
    MemoryController::PatcherController["LuaUnlocker"]->Restore();*/

    std::vector<std::string> keysToRemove = { "StorePageScan", "DriverCheck", "MemoryCheck", "Lua_Str_Check", "ModuleCheck" };
    for (const auto& key : keysToRemove)
    {
        auto it = MemoryController::DetourPatcher.find(key);
        if (it != MemoryController::DetourPatcher.end())
        {
            it->second->Remove();
            delete it->second;
            MemoryController::DetourPatcher.erase(it);
        }
    }
}

void Warden::ReapplyHacks()
{
    if (Loadedhacks.empty())
        return;

    for (const auto& key : Loadedhacks)
    {
        auto it = MemoryController::PatcherController.find(key);
        if (it != MemoryController::PatcherController.end())
        {
            it->second->Apply();
            // Remove the hack name from Loadedhacks
            Loadedhacks.erase(std::remove(Loadedhacks.begin(), Loadedhacks.end(), key), Loadedhacks.end());
        }
    }
}



void Warden::Hooks(DWORD Structure, DWORD Vtable)
{
    if (Vtable == NULL || Structure == NULL)
        return;

    DWORD StorePageScanInfo = ReadDWORD(ReadDWORD(ReadDWORD(Structure + 0x7B8)));
    DWORD MemoryCheckAddress = ReadDWORD(Vtable + WardenEnum::MemoryCheck);
    DWORD DriverCheckAddress = ReadDWORD(Vtable + WardenEnum::DriverCheck);
    DWORD ModuleCheckAddress = ReadDWORD(Vtable + WardenEnum::ModuleCheck);
    DWORD TimingCheckAddress = ReadDWORD(Vtable + WardenEnum::TimingCheck);


    if (MemoryCheckAddress == NULL 
    ||   StorePageScanInfo == NULL 
    ||  DriverCheckAddress == NULL 
    ||  ModuleCheckAddress == NULL 
    ||  TimingCheckAddress == NULL)
        return;

    Loggin(true, "Warden_Scans.txt", "[+]  Starting Warden Handler\n");
    Loggin(true, "Warden_Scans.txt", "[+]  WardenStruct       : 0x%x\n", Structure);
    Loggin(true, "Warden_Scans.txt", "[+]  Vtable             : 0x%x\n", Vtable);
    Loggin(true, "Warden_Scans.txt", "[+]  PageScan           : 0x%x\n", StorePageScanInfo);
    Loggin(true, "Warden_Scans.txt", "[+]  MemoryCheck        : 0x%x\n", MemoryCheckAddress);
    Loggin(true, "Warden_Scans.txt", "[+]  DriverCheck        : 0x%x\n", DriverCheckAddress);
    Loggin(true, "Warden_Scans.txt", "[+]  ModuleCheck        : 0x%x\n", ModuleCheckAddress);
    Loggin(true, "Warden_Scans.txt", "[+]  TimingCheck        : 0x%x\n", TimingCheckAddress);
    Loggin(true, "Warden_Scans.txt", "[+]  Lua_String_Check   : 0x%x\n", 0x00819210);
    Loggin(true, "Warden_Scans.txt", "[+]  Warden Handler Finished\n\n");

    OrignalMemoryCheck = (_MemoryCheck)MemoryCheckAddress;
    MemoryController::DetourPatcher["MemoryCheck"] = new DetourManager(MemoryCheckAddress, &(PVOID&)OrignalMemoryCheck, Warden::MemoryCheck);

    pPageCheckOriginal = (PageCheckOriginal)StorePageScanInfo;
    MemoryController::DetourPatcher["StorePageScan"] = new DetourManager(StorePageScanInfo, &(PVOID&)pPageCheckOriginal, Warden::PageCheck);

    OriginalDriverCheck = (DriverCheckType)DriverCheckAddress;
    MemoryController::DetourPatcher["DriverCheck"] = new DetourManager(DriverCheckAddress, &(PVOID&)OriginalDriverCheck, Warden::DriverCheck);

    MemoryController::DetourPatcher["Lua_Str_Check"] = new DetourManager(0x00819210, &(PVOID&)OrignalLua_String_Check, Warden::Lua_String_Check);

    OriginalModuleCheck = (_ModuleCheck)ModuleCheckAddress;
    MemoryController::DetourPatcher["ModuleCheck"] = new DetourManager(ModuleCheckAddress, &(PVOID&)OriginalModuleCheck, Warden::Warden_ModuleCheck);

    //MemoryController::PatcherController["AVRPatch"]->Apply();
    //MemoryController::PatcherController["LanguagePatch"]->Apply();
    //MemoryController::PatcherController["LuaUnlocker"]->Apply();
    //ReapplyHacks();

    IsApplied = true;

}