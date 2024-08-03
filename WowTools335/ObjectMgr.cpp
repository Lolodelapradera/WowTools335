#pragma once
#include "ObjectMgr.h"
#include "UnitFields.h"
#include "Helperfunctions.h"
#include "ObjectTypes.h"
#include "GameObject.h"

UINT64 ObjectMgr::GetLocalPlayerGuid()
{
	return ((unsigned long long(__cdecl*)())0x4d3790)();
}
UINT64 ObjectMgr::GetLocalTargetGuid()
{
	return *(__int64*)0x00BD07B0;
}
UINT ObjectMgr::GetLocalPlayerAddress()										//similar to GetPlayerAddr() in OM.hpp
{
	return GetObjectPointer(GetLocalPlayerGuid(), TYPEMASK_PLAYER);
}
UINT ObjectMgr::GetLocalTargetAddress(int type_mask)
{
	return GetObjectPointer(GetLocalTargetGuid(), type_mask);
}

UINT64 ObjectMgr::GetRaidMemberGuid(int index)
{
	UINT64 base = *(UINT64*)(0x00BEB568 + 4 * index);
	if (base > 0)
	{
		return *(UINT64*)(base);
	}
	return 0;
}
std::vector<UINT64> ObjectMgr::GetListRaidMembersGuid()
{
	std::vector<UINT64> Guids{};

	if (*(int*)(0x00BEB608) > 0)
	{
		for (size_t i = 0; i < 40; i++)
		{
			UINT64 guid = GetRaidMemberGuid(i);
			if (guid > 0)
			{
				Guids.push_back(guid);
			}
		}
	}
	else
	{
		UINT64 Member1 = *(UINT64*)Party::Member1GUID;
		if (Member1 > 0)
			Guids.push_back(Member1);

		UINT64 Member2 = *(UINT64*)Party::Member2GUID;
		if (Member2 > 0)
			Guids.push_back(Member2);

		UINT64 Member3 = *(UINT64*)Party::Member3GUID;
		if (Member3 > 0)
			Guids.push_back(Member3);

		UINT64 Member4 = *(UINT64*)Party::Member4GUID;
		if (Member4 > 0)
			Guids.push_back(Member4);

		if (Guids.size() > 1)
			Guids.push_back(GetLocalPlayerGuid());
	}

	return Guids;
}

bool ObjectMgr::enumObjects(EnumFunc_t func)
{
	return ((int(*)(int(*)(guid_t, void*), void*))0x004D4B30)([](guid_t guid, void* udata) -> int {
		return (*(EnumFunc_t*)udata)(guid);
		}, &func);
}
GameObjectNative* ObjectMgr::find(guid_t guid, unsigned flags)
{
	return ((GameObjectNative * (*)(guid_t, unsigned, const char*, unsigned))0x004D4DB0)(guid, flags, NULL, 0);
}

char* ObjectMgr::guid2hex(guid_t guid, char* hex)
{
	return ((char* (*)(guid_t, char*))0x0074D0D0)(guid, hex);
}
guid_t ObjectMgr::hex2guid(const char* str)
{
	return ((guid_t(*)(const char*))0x0074D120)(str);
}

guid_t ObjectMgr::GetObjGuid(UINT BaseAddress)
{
	if (BaseAddress == 0)
		return 0;
	return GetDescriptor<guid_t>(BaseAddress, OBJECT_FIELD_GUID);
}
guid_t ObjectMgr::GetObjTargetGuid(UINT BaseAddress)
{
	if (BaseAddress == 0)
		return 0;
	return GetDescriptor<guid_t>(BaseAddress, UNIT_FIELD_TARGET);
}

UINT ObjectMgr::GetObjectPointer(UINT64 guid, int type_mask)
{
	return  guid ? ((int(__cdecl*)(UINT64, int))0x004D4DB0)(guid, type_mask) : 0;
}
int ObjectMgr::GetVirtualFuncAddr(UINT BaseAddress, const int offset)
{
    return BaseAddress ? *(int*)(*(int*)BaseAddress + 4 * offset) : 0;
}

int ObjectMgr::GetDescriptors(UINT BaseAddress)
{
	if (!BaseAddress)
	{
		return 0;
	}
	return *(int*)(BaseAddress + 0x08);
}
void* ObjectMgr::GetPointerDescriptor(UINT BaseAddress, const int offset)
{
	return (void*)(GetDescriptors(BaseAddress) + offset * 4);
}
int ObjectMgr::GetObjectDescriptor(UINT BaseAddress, const int offset)
{
	return GetDescriptor2<int>(BaseAddress, offset);
}

template<typename DSC>
DSC ObjectMgr::GetDescriptor(UINT BaseAddress, int offset)
{
    int desc = GetDescriptors(BaseAddress);
    if (desc == 0) return DSC(0);
    UINT field = offset * 4;
    return *(DSC*)(desc + field);
}
template<typename DSC>
DSC ObjectMgr::GetDescriptor2(UINT BaseAddress, const int offset)
{
    int desc = GetDescriptors(BaseAddress);
    return desc ? *(DSC*)(desc + offset) : DSC(0);
}
template<typename DSC>
DSC ObjectMgr::GetDescriptorAddr(UINT BaseAddress, const int offset)
{
    int desc = GetDescriptors(BaseAddress);
    return (DSC)(desc + offset * 4);
}

UINT ObjectMgr::GetObjectEntry(UINT BaseAddress)
{
    return  GetDescriptor2<UINT>(BaseAddress, 0xC);
}
unsigned char* ObjectMgr::GetUnitBytes00(UINT BaseAddress)
{
	return (unsigned char*)GetPointerDescriptor(BaseAddress, UNIT_FIELD_BYTES_0);
}

char* ObjectMgr::GetName(UINT BaseAddress)
{
    if (BaseAddress == 0)
        return "";
    return ((char* (__thiscall*)(int))GetVirtualFuncAddr(BaseAddress, 54))(BaseAddress);
}
int ObjectMgr::GetType(UINT BaseAddress)
{
	if (BaseAddress == 0)
		return 0;

	int results = *(int*)(BaseAddress + 0x14);

	return results;
}
std::string ObjectMgr::GetRaceString(UINT BaseAddress)
{
	unsigned char* r = (unsigned char*)GetPointerDescriptor(BaseAddress, UNIT_FIELD_BYTES_0);
	switch (r[1])
	{
	case 1:
		return "Warrior";
	case 2:
		return "Paladin";
	case 3:
		return "Hunter";
	case 4:
		return "Rogue";
	case 5:
		return "Priest";
	case 6:
		return "Death Knight";
	case 7:
		return "Shaman";
	case 8:
		return "Mage";
	case 9:
		return "Warlock";
	case 11:
		return "Druid";
	default:
		return "None";
	}
}
int ObjectMgr::GetRaceInt(UINT BaseAddress)
{
	if (BaseAddress == 0) return -1;
	return ObjectMgr::GetDescriptor<int>(BaseAddress, UnitFields::UNIT_FIELD_FACTIONTEMPLATE);;
}
int ObjectMgr::GetLevel(UINT BaseAddress)
{
	if (BaseAddress == 0)
		return 0;

	int results = ObjectMgr::GetDescriptor<int>(BaseAddress, UnitFields::UNIT_FIELD_LEVEL);
	return results;
}
Vector3 ObjectMgr::GetPosition(UINT BaseAddress)
{
	Vector3 res;
	if (BaseAddress == 0)
		return res;

	((void(__thiscall*)(int, Vector3*))GetVirtualFuncAddr(BaseAddress, 12))(BaseAddress, &res);
	return res;
}
float ObjectMgr::GetRotation(UINT addr)
{
	return addr ? ((float(__thiscall*)(int))GetVirtualFuncAddr(addr, 14))(addr) : 0;
}
float ObjectMgr::GetMoveSpeed(UINT BaseAddress)
{
	return *(float*)(*(DWORD*)(BaseAddress + 0xD8) + 0x8C);
}
int ObjectMgr::GetChanneledSpellId(UINT BaseAddress)
{
	return BaseAddress ? *(int*)(BaseAddress + 0xA80) : 0;
}
int ObjectMgr::GetCastingSpellId(UINT BaseAddress)
{
	return BaseAddress ? *(int*)(BaseAddress + 0xA6C) : 0;
}

int ObjectMgr::GetHealth(UINT BaseAddress)
{
    return GetDescriptor<int>(BaseAddress, UNIT_FIELD_HEALTH);
}
int ObjectMgr::GetMaxHealth(UINT BaseAddress)
{
    return GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXHEALTH);
}
double ObjectMgr::GetHealthPercent(UINT BaseAddress)
{
    if (BaseAddress == 0) return 0;
    return RoundNumber((GetHealth(BaseAddress) / (double)GetMaxHealth(BaseAddress)) * 100);
}

PowerType ObjectMgr::GetPowerType(UINT BaseAddress) { return (PowerType)GetUnitBytes00(BaseAddress)[3]; }
int ObjectMgr::GetMaxPowerByType(UINT BaseAddress, PowerType powerType)
{
	switch (powerType)
	{
	case POWER_MANA:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER1);
	case POWER_RAGE:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER2);
	case POWER_ENERGY:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER3);
	case POWER_FOCUS:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER4);
	case POWER_HAPPINESS:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER5);
	case POWER_RUNE:
	case POWER_RUNIC_POWER:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_MAXPOWER7);
	default:
		return 0;
	}
}
int ObjectMgr::GetPowerByType(UINT BaseAddress, PowerType powerType)
{
	switch (powerType)
	{
	case POWER_MANA:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER1);
	case POWER_RAGE:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER2);
	case POWER_ENERGY:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER3);
	case POWER_FOCUS:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER4);
	case POWER_HAPPINESS:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER5);
	case POWER_RUNE:
	case POWER_RUNIC_POWER:
		return  ObjectMgr::GetDescriptor<int>(BaseAddress, UNIT_FIELD_POWER7);
	default:
		return 0;
	}
}
double ObjectMgr::GetPowerPercentage(UINT BaseAddress)
{
	if (BaseAddress == 0) return 0;
	auto powerType = GetPowerType(BaseAddress);
	int min = GetPowerByType(BaseAddress, powerType);
	int max = GetMaxPowerByType(BaseAddress, powerType);

	if (min <= 0 || max <= 0)
		return 0;

	double GetPower = (static_cast<double>(min) / static_cast<double>(max)) * 100.0;
	if (GetPower <= 0.0)
	{
		return 0.0;
	}

	return RoundNumber(GetPower);
}

bool ObjectMgr::GetUnitFlags(UINT BaseAddress, int FlagType)
{
	if (BaseAddress == 0)
		return false;

	return GetDescriptor<int>(BaseAddress, FlagType) != 0;
}
bool ObjectMgr::HasFlagRaw(UINT BaseAddress, const int idx, const int flag)
{
	int flags = GetDescriptor<int>(BaseAddress, idx);
	return (flags & flag) != 0;
}
bool ObjectMgr::HasFlagRaw(UINT BaseAddress, const int idx)
{
	int flags = GetDescriptor<int>(BaseAddress, idx);
	return (flags) != 0;
}
bool ObjectMgr::HasFlag(UINT BaseAddress, int flag)
{
	if (BaseAddress == 0) return false;
	return HasFlagRaw(BaseAddress, UNIT_FIELD_FLAGS, flag);
}
bool ObjectMgr::HasDynamicFlag(UINT BaseAddress, int flag)
{
	if (BaseAddress == 0) return false;

	return HasFlagRaw(BaseAddress, UNIT_DYNAMIC_FLAGS, flag);
}

bool ObjectMgr::CanAttack(UINT BaseAddress, UINT TargetAddress)
{
	if (BaseAddress == 0 || TargetAddress == 0)
		return false;
	return ((bool(__thiscall*)(int, int))0x00729740)(BaseAddress, TargetAddress);
}
bool ObjectMgr::IsInCombat(UINT BaseAddress)
{
	return HasFlag(BaseAddress, 0x00080000);
}
bool ObjectMgr::IsAffectingCombat(UINT BaseAddress)
{
	return (*(DWORD*)(*(DWORD*)(BaseAddress + 0xD0) + 0xD4) & 0x80000) != 0;
}
bool ObjectMgr::IsLootable(UINT BaseAddress)
{
	return HasDynamicFlag(BaseAddress, 0x0001);
}
bool ObjectMgr::IsSkinnable(UINT BaseAddress)
{
	return HasDynamicFlag(BaseAddress, 0x04000000);
}
bool ObjectMgr::IsDead(UINT BaseAddress)
{
	if (BaseAddress == 0) return false;
	return GetHealth(BaseAddress) <= 0;
	//HasDynamicFlag(Addr, 0x0020);
}
bool ObjectMgr::IsTapped(UINT BaseAddress)
{
	return HasDynamicFlag(BaseAddress, 0x0004);
}
void ObjectMgr::Interact(UINT BaseAddress)
{
	if (BaseAddress)
	{
		((void(__thiscall*)(int))GetVirtualFuncAddr(BaseAddress, 44))(BaseAddress);
	}
}
guid_t ObjectMgr::CreatedBy(UINT BaseAddress)
{
	if (BaseAddress == 0)
		return 0;
	return GetDescriptor<guid_t>(BaseAddress, OBJECT_FIELD_CREATED_BY);
}
uint64_t ObjectMgr::SummonedBy(UINT BaseAddress)
{
	return ObjectMgr::GetDescriptor<uint64_t>(BaseAddress, UNIT_FIELD_SUMMONEDBY);
}

void ObjectMgr::SetRawFacing(UINT BaseAddress, float angle)
{
	if (angle < 0.0f)
		angle += PI * 2;
	if (angle > PI * 2)
		angle -= PI * 2;
	((char* (__thiscall*)(int, int, float))0x0072EA50)(BaseAddress, PerformanceCount(), angle);
}
float ObjectMgr::GetSideFaceRotation(UINT BaseAddress, float halfShootCone, Vector3 position)
{
	auto rot = GetRotation(BaseAddress);
	Vector3 pos = GetPosition(BaseAddress);
	float angle = NormalizeRadian(CalculateFacingAngle(pos, position));
	float faceTo0 = NormalizeRadian(angle - rot);
	float faceDiff = faceTo0;
	bool objectOnRightSide = false;
	float sideFaceDiff = 0;

	if (faceTo0 >= PI)
	{
		faceDiff = 2 * PI - faceTo0;
		objectOnRightSide = true;
	}

	if (faceDiff > halfShootCone)
	{
		sideFaceDiff = faceDiff - halfShootCone;

		if (!objectOnRightSide)
		{
			return sideFaceDiff + rot;
		}
		else
		{
			return rot - sideFaceDiff;
		}
	}
	else
	{
		return rot;
	}
}
bool ObjectMgr::IsFacing(UINT BaseAddress, float angle, Vector3 position)
{
	return GetRotation(BaseAddress) == GetSideFaceRotation(BaseAddress, angle, position);
}
bool ObjectMgr::FacePostion(UINT BaseAddress, float angle, Vector3 position)
{
	if (!IsFacing(BaseAddress, angle, position))
	{
		float sfr = GetSideFaceRotation(BaseAddress, angle, position);
		sfr = sfr < PI ? sfr - angle / 100 : sfr + angle / 100;

		SetRawFacing(BaseAddress, sfr);
		return true;
	}
	return false;
}

int ObjectMgr::GetDynamicObjectSpellId(UINT BaseAddress)
{
	if (BaseAddress == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(BaseAddress, 0x9);
}
int ObjectMgr::GetDynamicObjectRadius(UINT BaseAddress)
{
	if (BaseAddress == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(BaseAddress, 0xA);
}
int ObjectMgr::GetDynamicObjectCastTime(UINT BaseAddress)
{
	if (BaseAddress == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(BaseAddress, 0xB);
}