#include "Patch.h"
#include <cstring>
#include <iostream>

Patch::Patch(int target_addr, std::initializer_list<byte> bytes)
    : MemoryOperation((byte*)target_addr, bytes), Address(target_addr)
{
    this->_Address = target_addr;
    DWORD old_protection_;
    DWORD _;
    VirtualProtect(target, bytes.size(), PAGE_EXECUTE_READWRITE, &old_protection_);

    original_bytes.resize(bytes.size());
    memcpy(original_bytes.data(), target, bytes.size());
    VirtualProtect(target, bytes.size(), old_protection_, &_);

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
    //__try {
    DWORD old_protection_;
    DWORD _;
    VirtualProtect(target, new_bytes.size(), PAGE_EXECUTE_READWRITE, &old_protection_);
    memcpy(target, new_bytes.data(), new_bytes.size());
    VirtualProtect(target, new_bytes.size(), old_protection_, &_);
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) {
    //    std::cout << "Access violation exception caught!" << std::endl;
    //}
    
    
}

void Patch::Restore()
{
    this->IsModified = false;
    //__try {
    DWORD old_protection_;
    DWORD _;
    VirtualProtect(target, original_bytes.size(), PAGE_EXECUTE_READWRITE, &old_protection_);
    memcpy(target, original_bytes.data(), original_bytes.size());
    VirtualProtect(target, original_bytes.size(), old_protection_, &_);

    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) {
    //    std::cout << "Access violation exception caught!" << std::endl;
    //}
    
}
