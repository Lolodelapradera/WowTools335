#pragma once
#include <cstdint>

typedef uint64_t guid_t;
struct ObjectEntry {
    guid_t guid;
    int type;
    int entry;
    float scaleX;
    int padding;
};
static_assert(sizeof(ObjectEntry) == 0x18);