#include "Warden.h"
#include "WardenHelpers.h"
#include "WardenEnums.h"

bool Warden::IsApplied = false;
DWORD Warden::WoWBase = 0;
void Warden::Initiative()
{
    WoWBase = GetBaseAddress();
    MemoryController::DetourPatcher["Warden_Handler"] = new DetourManager(0x007DA850, &(PVOID&)OriginalWardenDataHandler, Warden::WardenDataHandler);
    //MemoryController::DetourPatcher["Warden_ShutdownAndUnload"] = new DetourManager(0x08dA420, &(PVOID&)OriginalShutdownAndUnload, Warden::ShutdownAndUnload);
}

void Warden::Dispose()
{
    RemoveHooks();
    MemoryController::DetourPatcher["Warden_Handler"]->Remove();
    //MemoryController::DetourPatcher["Warden_ShutdownAndUnload"]->Remove();
}

void Warden::RestoreHacks()
{
    for (const auto& key : MemoryController::PatcherController)
        if (key.second->IsModified)
            key.second->Restore();
    Loggin(true, "Warden_Scans.txt", "[-]  Hacks\t\t: Removed!\n");
}

void Warden::ApplyHacks()
{
    for (const auto& key : MemoryController::PatcherController)
        if (key.second->IsToggled)
            key.second->Apply();
    Loggin(true, "Warden_Scans.txt", "[+]  Hacks\t\t: Applied!\n");
}

bool Warden::ApplyHooks(DWORD Structure, DWORD Vtable)
{
    if (!IsApplied)
    {
        Loggin(true, "Warden_Scans.txt", "\n     -- Applying Warden Hooks --\n");

        if (Vtable == NULL || Structure == NULL)
        {
            Loggin(true, "Warden_Scans.txt", "[+]  ERROR: Vtable->0x%x Struct->0x%x\n");
            return false;
        }

        DWORD StorePageScanInfo = ReadDWORD(ReadDWORD(ReadDWORD(Structure + 0x7B8)));
        DWORD MemoryCheckAddress = ReadDWORD(Vtable + WardenEnum::MemoryCheck);
        DWORD DriverCheckAddress = ReadDWORD(Vtable + WardenEnum::DriverCheck);
        DWORD ModuleCheckAddress = ReadDWORD(Vtable + WardenEnum::ModuleCheck);
        DWORD TimingCheckAddress = ReadDWORD(Vtable + WardenEnum::TimingCheck);

        Loggin(true, "Warden_Scans.txt", "[+]  WardenStruct       : 0x%x\n", Structure);
        Loggin(true, "Warden_Scans.txt", "[+]  Vtable             : 0x%x\n", Vtable);
        Loggin(true, "Warden_Scans.txt", "[+]  PageScan           : 0x%x\n", StorePageScanInfo);
        Loggin(true, "Warden_Scans.txt", "[+]  MemoryCheck        : 0x%x\n", MemoryCheckAddress);
        Loggin(true, "Warden_Scans.txt", "[+]  DriverCheck        : 0x%x\n", DriverCheckAddress);
        Loggin(true, "Warden_Scans.txt", "[+]  ModuleCheck        : 0x%x\n", ModuleCheckAddress);
        Loggin(true, "Warden_Scans.txt", "[+]  TimingCheck        : 0x%x\n", TimingCheckAddress);
        Loggin(true, "Warden_Scans.txt", "[+]  Lua_String_Check   : 0x%x\n", 0x00819210);

        if (MemoryCheckAddress == NULL
            || StorePageScanInfo == NULL
            || DriverCheckAddress == NULL
            || ModuleCheckAddress == NULL
            || TimingCheckAddress == NULL)
        {
            Loggin(true, "Warden_Scans.txt", "[+]  ERROR: See Address table above!\n");
            return false;
        }

        OrignalMemoryCheck = (_MemoryCheck)MemoryCheckAddress;
        MemoryController::DetourPatcher["MemoryCheck"] = new DetourManager(MemoryCheckAddress, &(PVOID&)OrignalMemoryCheck, Warden::MemoryCheck);

        pPageCheckOriginal = (PageCheckOriginal)StorePageScanInfo;
        MemoryController::DetourPatcher["StorePageScan"] = new DetourManager(StorePageScanInfo, &(PVOID&)pPageCheckOriginal, Warden::PageCheck);

        OriginalDriverCheck = (DriverCheckType)DriverCheckAddress;
        MemoryController::DetourPatcher["DriverCheck"] = new DetourManager(DriverCheckAddress, &(PVOID&)OriginalDriverCheck, Warden::DriverCheck);

        MemoryController::DetourPatcher["Lua_Str_Check"] = new DetourManager(0x00819210, &(PVOID&)OrignalLua_String_Check, Warden::Lua_String_Check);

        OriginalModuleCheck = (_ModuleCheck)ModuleCheckAddress;
        MemoryController::DetourPatcher["ModuleCheck"] = new DetourManager(ModuleCheckAddress, &(PVOID&)OriginalModuleCheck, Warden::Warden_ModuleCheck);

        ApplyHacks();

        IsApplied = true;
        Loggin(true, "Warden_Scans.txt", "     -- Warden Hooks - APPLIED --\n\n");
        return true;
    }
    Loggin(true, "Warden_Scans.txt", "     -- Warden Hooks - FAILED --\n\n");
    return false;
}

void Warden::RemoveHooks()
{
    if (IsApplied)
    {
        Loggin(true, "Warden_Scans.txt", "\n     -- Removing Warden Hooks --\n");

        IsApplied = false;
        RestoreHacks();

        std::vector<std::string> keysToRemove = { "StorePageScan", "DriverCheck", "MemoryCheck", "Lua_Str_Check", "ModuleCheck" };
        for (const auto& key : keysToRemove)
        {
            auto it = MemoryController::DetourPatcher.find(key);
            if (it != MemoryController::DetourPatcher.end())
            {
                std::string padding = "\t";
                if (key.size() <= 11)
                    padding += "\t";
                Loggin(true, "Warden_Scans.txt", "[-]  %s%s: 0x%x\n", key.c_str(), padding.c_str(), it->second->Address);
                it->second->Remove();
                delete it->second;
                MemoryController::DetourPatcher.erase(it);
            }
        }

        Loggin(true, "Warden_Scans.txt", "     -- Warden Hooks - REMOVED --\n\n");
    }
}