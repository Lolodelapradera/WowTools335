#pragma once
#include "ObjectEntry.h"

struct UnitEntry : public ObjectEntry {
    guid_t charm;
    guid_t summon;
    guid_t critter;
    guid_t charmedBy;
    guid_t summonedBy;
    guid_t createdBy;
    guid_t target;
    guid_t channelObject;
    uint32_t channelSpell;
    uint32_t bytes0;
    uint32_t health;
    uint32_t power[7];
    uint32_t maxHealth;
    uint32_t maxPower[7];
    uint32_t powerRegenFlatModifier[7];
    uint32_t powerRegenInterruptedFlatModifier[7];
    uint32_t level;
    uint32_t factionTemplate;
    uint32_t virtualItemSlotId[3];
    uint32_t flags;
    uint32_t flags2;

    char gap[0x15C];
};
static_assert(sizeof(UnitEntry) == 0x250);

