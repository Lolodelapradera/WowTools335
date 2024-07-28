#include "Helperfunctions.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "UnitFields.h"


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