#pragma once
#ifndef PATCH_H
#define PATCH_H

#include <initializer_list>
#include <vector>
#include <windows.h>
#include "MemoryOperation.h"

class Patch : public MemoryOperation
{
public:
    Patch(int target_addr, std::initializer_list<byte> bytes);
    //Patch(int target_addr, std::initializer_list<byte> bytes, bool apply);
    ~Patch();

    void Apply();
    void Restore();
    bool IsModified = false;
    bool IsToggled = false;

private:
    int Address;
    std::vector<byte> original_bytes;
};

#endif // PATCH_H
