#pragma once

#include "SharedHeaders.h"
#include "Powers.h"
#include "ObjectEntry.h"
#include "ObjectTypes.h"


#pragma warning(disable : 4067)

const float PI{ 3.141592653589793f };
double RoundNumber(double f);
int Health(UINT ptr);
int MaxHealth(UINT ptr);
double HealthPercent(UINT ptr);
unsigned char* UnitBytes00(UINT addr);
int PowerType(UINT addr);
int GetMaxPowerByType(UINT Addr, Powers power);
int GetPowerByType(UINT Addr, Powers power);
double GetPowerPercentage(UINT addr);
std::string GetRace(int Ptr);
UINT GetObjectEntry(UINT addr);
bool CanAttack(UINT Addr1, UINT Addr2);
guid_t GetObjGuid(UINT addr);
guid_t CreatedBy(UINT addr);
uint64_t GetRaidMemberGuid(int index);
bool UnitIsInCombat(UINT addr);
std::vector<uint64_t> GetPartyGUID();
guid_t GetObjTargetGuid(UINT addr);
int GetLevel(UINT addr);
int Type(UINT addr);
bool IsSkinnable(UINT addr);
bool IsLootable(UINT addr);
bool IsDead(UINT addr);
bool IsTapped(UINT Addr);
uint64_t SummonedBy(UINT Addr);
int ChanneledId(UINT addr);
int CastingId(UINT addr);

inline int PerformanceCount();
//bool Face(float angle, Vector position);
//bool IsFacing(float angle, Vector position);
//float GetSideFaceRotation(float halfShootCone, Vector position);
//float CalculateNeededFacing(Vector start, Vector end);
float NormalizeRadian(float radian);
void SetFacing(float angle);
float GetUnitSpeed(UINT Addr);
bool UnitAffectingCombat(UINT Addr);
int GetWowRace(UINT addr);

bool UnitFlag(UINT addr, int arg);
bool UnitDynamicFlag(UINT addr, int arg);

int GetSpellIdDynamicObject(UINT addr);
int GetRADIUSDynamicObject(UINT addr);
int GetCastTimDynamicObject(UINT addr);