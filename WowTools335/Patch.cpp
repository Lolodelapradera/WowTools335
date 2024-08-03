#include "Patch.h"
#include <cstring>
#include <iostream>

Patch::Patch(int target_addr, std::initializer_list<byte> bytes)
    : MemoryOperation((byte*)target_addr, bytes), Address(target_addr)
{
    this->_Address = target_addr;
    DWORD old_protection_;
    VirtualProtect(target, bytes.size(), PAGE_EXECUTE_READWRITE, &old_protection_);

    original_bytes.resize(bytes.size());
    memcpy(original_bytes.data(), target, bytes.size());
    /*Apply();*/
}

//Patch::Patch(int target_addr, std::initializer_list<byte> bytes, bool apply)
//    : MemoryOperation((byte*)target_addr, bytes), Address(target_addr), IsModified(apply)
//{
//    DWORD old_protection_;
//    VirtualProtect(target, bytes.size(), PAGE_EXECUTE_READWRITE, &old_protection_);
//
//    original_bytes.assign(bytes.begin(), bytes.end());
//}

Patch::~Patch()
{
    Restore();
}

void Patch::Apply()
{
    this->IsModified = true;
   
    memcpy(target, new_bytes.data(), new_bytes.size());
}

void Patch::Restore()
{
    this->IsModified = false;
    memcpy(target, original_bytes.data(), original_bytes.size());
}
