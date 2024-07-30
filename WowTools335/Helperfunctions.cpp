#include "Helperfunctions.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "UnitFields.h"
#include "Vector3.h"
#include <iomanip>
#include <basetsd.h>

#pragma warning(disable : 4067)

inline int PerformanceCount() { return ((int(__cdecl*)())0x0086AE20)(); }
double RoundNumber(double f)
{
	return std::round(f * 10.0) / 10.0;
}

int Health(UINT ptr)
{
	return ObjectMgr::GetDescriptor<int>(ptr, UNIT_FIELD_HEALTH);

}

int MaxHealth(UINT ptr)
{
	return  ObjectMgr::GetDescriptor<int>(ptr, UNIT_FIELD_MAXHEALTH);
}

double HealthPercent(UINT ptr)
{
	if (ptr == 0) return 0;
	return RoundNumber((Health(ptr) / (double)MaxHealth(ptr)) * 100);
}

unsigned char* UnitBytes00(UINT addr)
{
	return (unsigned char*)ObjectMgr::GetPointerDescriptor(addr, UNIT_FIELD_BYTES_0);
}

int PowerType(UINT addr) { return UnitBytes00(addr)[3]; }

int GetMaxPowerByType(UINT Addr, Powers power)
{
	switch (power)
	{
	case POWER_MANA:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER1);
	case POWER_RAGE:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER2);
	case POWER_ENERGY:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER3);
	case POWER_FOCUS:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER4);
	case POWER_HAPPINESS:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER5);
	case POWER_RUNE:
	case POWER_RUNIC_POWER:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_MAXPOWER7);
	default:
		return 0;
	}
}

int GetPowerByType(UINT Addr, Powers power)
{
	switch (power)
	{
	case POWER_MANA:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER1);
	case POWER_RAGE:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER2);
	case POWER_ENERGY:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER3);
	case POWER_FOCUS:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER4);
	case POWER_HAPPINESS:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER5);
	case POWER_RUNE:
	case POWER_RUNIC_POWER:
		return  ObjectMgr::GetDescriptor<int>(Addr, UNIT_FIELD_POWER7);
	default:
		return 0;
	}
}
double GetPowerPercentage(UINT addr)
{
	if (addr == 0) return 0;
	int GetPowerType = PowerType(addr);
	int Minimum = GetPowerByType(addr, (Powers)GetPowerType);
	int Maximum = GetMaxPowerByType(addr, (Powers)GetPowerType);

	if (Minimum <= 0 || Maximum <= 0)
		return 0;

	double GetPower = (static_cast<double>(Minimum) / static_cast<double>(Maximum)) * 100.0;
	if (GetPower <= 0.0)
	{
		return 0.0;
	}

	return RoundNumber(GetPower);
}

std::string GetRace(int Ptr)
{
	unsigned char* r = (unsigned char*)ObjectMgr::GetPointerDescriptor(Ptr, UNIT_FIELD_BYTES_0);
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

UINT GetObjectEntry(UINT addr)
{
	return  ObjectMgr::GetDescriptor2<UINT>(addr, 0xC);
}
bool CanAttack(UINT Addr1, UINT Addr2)
{
	if (Addr1 == 0 || Addr2 == 0)
		return false;
	return ((bool(__thiscall*)(int, int))0x00729740)(Addr1, Addr2);
}

bool GetUnitFlags(UINT Addr1, int FlagType)
{
	if (Addr1 == 0)
		return false;

	return  ObjectMgr::GetDescriptor<int>(Addr1, FlagType) != 0;
}

guid_t GetObjGuid(UINT addr)
{
	if (addr == 0)
		return 0;
	return  ObjectMgr::GetDescriptor<guid_t>(addr, OBJECT_FIELD_GUID);
}
guid_t GetObjTargetGuid(UINT addr)
{
	if (addr == 0)
		return 0;
	return  ObjectMgr::GetDescriptor<guid_t>(addr, UNIT_FIELD_TARGET);
}

guid_t CreatedBy(UINT addr)
{
	if (addr == 0)
		return 0;
	return  ObjectMgr::GetDescriptor<guid_t>(addr, OBJECT_FIELD_CREATED_BY);
}

// -------

std::string tohex16(UINT64 i)
{
	std::stringstream stream;
	stream << "0x" << std::setw(16) << std::setfill('0') << std::hex << std::uppercase << i;
	std::string result = stream.str();
	return result;
}

enum Party
{
	LeaderGUID = 0xBD1968,                  // 3.3.5
	Member1GUID = 0x00BD1940,                 // 3.3.5
	Member2GUID = Member1GUID + 0x8,        // 3.3.5
	Member3GUID = Member2GUID + 0x8,        // 3.3.5
	Member4GUID = Member3GUID + 0x8,        // 3.3.5
};

uint64_t GetRaidMemberGuid(int index)
{
	uint64_t base = *(uint64_t*)(0x00BEB568 + 4 * index);
	if (base > 0)
	{
		return *(uint64_t*)(base);
	}
	return 0;
}

inline unsigned long long PlayerGuid()
{
	return ((unsigned long long(__cdecl*)())0x4d3790)();
}


std::vector<uint64_t> GetPartyGUID()
{
	std::vector<uint64_t> Guids{};

	if (*(int*)(0x00BEB608) > 0)
	{
		for (size_t i = 0; i < 40; i++)
		{
			uint64_t guid = GetRaidMemberGuid(i);
			if (guid > 0)
			{
				Guids.push_back(guid);
			}
		}
	}
	else
	{
		uint64_t Member1 = *(uint64_t*)Party::Member1GUID;
		if (Member1 > 0)
			Guids.push_back(Member1);

		uint64_t Member2 = *(uint64_t*)Party::Member2GUID;
		if (Member2 > 0)
			Guids.push_back(Member2);

		uint64_t Member3 = *(uint64_t*)Party::Member3GUID;
		if (Member3 > 0)
			Guids.push_back(Member3);

		uint64_t Member4 = *(uint64_t*)Party::Member4GUID;
		if (Member4 > 0)
			Guids.push_back(Member4);

		if (Guids.size() > 1)
			Guids.push_back(PlayerGuid());
	}

	return Guids;
}

int GetVirtualFuncAddr(UINT Ptr, const int offset)
{
	return Ptr ? *(int*)(*(int*)Ptr + 4 * offset) : 0;
}

bool HasFlag(UINT BaseAddress, const int idx, const int flag)
{
	int flags = ObjectMgr::GetDescriptor<int>(BaseAddress, idx);
	return (flags & flag) != 0;
}

bool HasFlag(UINT BaseAddress, const int idx)
{
	int flags = ObjectMgr::GetDescriptor<int>(BaseAddress, idx);
	return (flags) != 0;
}

int GetLevel(UINT addr)
{
	if (addr == 0)
		return 0;

	int results = ObjectMgr::GetDescriptor<int>(addr, UnitFields::UNIT_FIELD_LEVEL);
	return results;
}

bool UnitIsInCombat(UINT addr)
{
	return HasFlag(addr, UNIT_FIELD_FLAGS, 0x00080000);
}

int Type(UINT addr)
{
	if (addr == 0)
		return 0;

	int results = *(int*)(addr + 0x14);

	return results;
}

bool IsLootable(UINT addr)
{
	return HasFlag(addr, UNIT_DYNAMIC_FLAGS, 0x0001);
}

bool IsSkinnable(UINT addr)
{
	return HasFlag(addr, UNIT_DYNAMIC_FLAGS, 0x04000000);
}

bool IsDead(UINT Addr)
{
	if (Addr == 0) return false;
	return Health(Addr) <= 0;
	//HasFlag(Addr, UNIT_DYNAMIC_FLAGS, 0x0020);
}

bool IsTapped(UINT Addr)
{
	return HasFlag(Addr, UNIT_DYNAMIC_FLAGS, 0x0004);
}

uint64_t SummonedBy(UINT Addr)
{
	return ObjectMgr::GetDescriptor<uint64_t>(Addr, UNIT_FIELD_SUMMONEDBY);
}

int ChanneledId(UINT addr)
{
	return addr ? *(int*)(addr + 0xA80) : 0;
}

int CastingId(UINT addr)
{
	return addr ? *(int*)(addr + 0xA6C) : 0;
}


inline uint64_t GetLocalPlayerGuid()								//similar to GetPlayerGuid() in OM.hpp
{
	return ((uint64_t(__cdecl*)())(0x004D3790))();				//ClntObjMgrGetActivePlayerGuid()
}

inline int GetLocalPlayer()										//similar to GetPlayerAddr() in OM.hpp
{
	uint64_t lpguid = GetLocalPlayerGuid();
	return lpguid ? ((int(__cdecl*)(long long, int))0x004D4DB0)(lpguid, TYPEMASK_PLAYER) : 0;
}


float Rotation(UINT addr)
{
	return addr ? ((float(__thiscall*)(int))GetVirtualFuncAddr(addr, 14))(addr) : 0;
}

/*
bool Face(float angle, Vector position)
{
	if (!IsFacing(angle, position))
	{
		float sfr = GetSideFaceRotation(angle, position);
		sfr = sfr < PI ? sfr - angle / 100 : sfr + angle / 100;

		SetFacing(sfr);
		return true;
	}
	return false;
}



bool IsFacing(float angle, Vector position)
{
	return Rotation(PlayerBaseAddr) == GetSideFaceRotation(angle, position);
}

float GetSideFaceRotation(float halfShootCone, Vector position)
{
	auto lpR = Rotation(PlayerBaseAddr);
	Vector pos = GetPosition(PlayerBaseAddr);
	float angle = NormalizeRadian(CalculateNeededFacing(pos, position));
	float faceTo0 = NormalizeRadian(angle - lpR);
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
			return sideFaceDiff + lpR;
		}
		else
		{
			return lpR - sideFaceDiff;
		}
	}
	else
	{
		return lpR;
	}
}
*/

float CalculateNeededFacing(Vector start, Vector end)
{
	return atan2((end.Y - start.Y), (end.X - start.X));
}

float NormalizeRadian(float radian) //ClampAngle
{
	while (radian < 0)
	{
		radian = radian + 2 * PI;
	}
	while (radian >= 2 * PI)
	{
		radian = radian - 2 * PI;
	}
	return radian;
}


void SetFacing(float angle)
{
	if (angle < 0.0f)
		angle += PI * 2;
	if (angle > PI * 2)
		angle -= PI * 2;
	int ipa = GetLocalPlayer();

	((char* (__thiscall*)(int, int, float))0x0072EA50)(ipa, PerformanceCount(), angle);
}


float GetUnitSpeed(UINT addr)
{
	return *(float*)(*(DWORD*)(addr + 0xD8) + 0x8C);
}

bool UnitAffectingCombat(UINT Addr)
{
	return (*(DWORD*)(*(DWORD*)(Addr + 0xD0) + 0xD4) & 0x80000) != 0;
}


int GetWowRace(UINT addr)
{
	if (addr == 0) return -1;
	return ObjectMgr::GetDescriptor<int>(addr, UnitFields::UNIT_FIELD_FACTIONTEMPLATE);;
}

int GetSpellIdDynamicObject(UINT addr)
{
	if (addr == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(addr, 0x9);
}

int GetRADIUSDynamicObject(UINT addr)
{
	if (addr == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(addr, 0xA);
}

int GetCastTimDynamicObject(UINT addr)
{
	if (addr == 0) return 0;

	return *(int*)ObjectMgr::GetDescriptorAddr<int>(addr, 0xB);
}

bool UnitFlag(UINT addr, int arg)
{
	if (addr == 0) return false;

	return HasFlag(addr, UNIT_FIELD_FLAGS, arg);
}

bool UnitDynamicFlag(UINT addr, int arg)
{
	if (addr == 0) return false;

	return HasFlag(addr, UNIT_DYNAMIC_FLAGS, arg);
}