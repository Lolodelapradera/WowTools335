#pragma once
#include "SharedHeaders.h"
#include "PowerType.h"
#include "Vector3.h"


using guid_t = uint64_t;
using EnumFunc_t = std::function<bool(guid_t)>;

enum Party
{
	LeaderGUID = 0xBD1968,                  // 3.3.5
	Member1GUID = 0x00BD1940,               // 3.3.5
	Member2GUID = Member1GUID + 0x8,        // 3.3.5
	Member3GUID = Member2GUID + 0x8,        // 3.3.5
	Member4GUID = Member3GUID + 0x8,        // 3.3.5
};

struct GameObjectNative;

class ObjectMgr {
public:
	static UINT LocalPlayerBaseAddress;
	static UINT LocalTargetBaseAddress;

	static UINT64 GetLocalPlayerGuid();
	static UINT64 GetLocalTargetGuid();
	static UINT GetLocalPlayerAddress();
	static UINT GetLocalTargetAddress(int type_mask);

	static UINT64 GetRaidMemberGuid(int index);
	static std::vector<UINT64> GetListRaidMembersGuid();

	static bool enumObjects(EnumFunc_t func);
	static GameObjectNative* find(guid_t guid, unsigned flags);

	static char* guid2hex(guid_t guid, char* buf);
	static guid_t hex2guid(const char* str);

	static guid_t GetObjGuid(UINT BaseAddress);
	static guid_t GetObjTargetGuid(UINT BaseAddress);

	static UINT GetObjectPointer(uint64_t guid, int type_mask);
	static int GetVirtualFuncAddr(UINT BaseAddress, const int offset);

	static int GetDescriptors(UINT BaseAddress);
	static void* GetPointerDescriptor(UINT BaseAddress, const int offset);
	static int GetObjectDescriptor(UINT BaseAddress, const int offset);

	template<typename DSC>
	static DSC GetDescriptor(UINT BaseAddress, int offset);
	template<typename DSC>
	static DSC GetDescriptor2(UINT BaseAddress, const int offset);
	template<typename DSC>
	static DSC GetDescriptorAddr(UINT BaseAddress, const int offset);

	static UINT GetObjectEntry(UINT BaseAddress);
	static unsigned char* GetUnitBytes00(UINT BaseAddress);

	static char* GetName(UINT BaseAddress);
	static int GetType(UINT BaseAddress);
	static std::string GetRaceString(UINT BaseAddress);
	static int GetRaceInt(UINT BaseAddress);
	static int GetLevel(UINT BaseAddress);
	static Vector3 GetPosition(UINT BaseAddress);
	static float GetRotation(UINT BaseAddress);
	static float GetMoveSpeed(UINT BaseAddress);
	static int GetChanneledSpellId(UINT BaseAddress);
	static int GetCastingSpellId(UINT BaseAddress);

	static int GetHealth(UINT BaseAddress);
	static int GetMaxHealth(UINT BaseAddress);
	static double GetHealthPercent(UINT BaseAddress);

	static PowerType GetPowerType(UINT BaseAddress);
	static int GetMaxPowerByType(UINT BaseAddress, PowerType powerType);
	static int GetPowerByType(UINT BaseAddress, PowerType powerType);
	static double GetPowerPercentage(UINT BaseAddress);

	static bool GetUnitFlags(UINT BaseAddress, int FlagType);
	static bool HasFlagRaw(UINT BaseAddress, const int idx, const int flag);
	static bool HasFlagRaw(UINT BaseAddress, const int idx);
	static bool HasFlag(UINT BaseAddress, int flag);
	static bool HasDynamicFlag(UINT BaseAddress, int flag);

	static bool CanAttack(UINT BaseAddress, UINT TargetAddress);
	static bool IsInCombat(UINT BaseAddress);
	static bool IsAffectingCombat(UINT BaseAddress);
	static bool IsLootable(UINT BaseAddress);
	static bool IsSkinnable(UINT BaseAddress);
	static bool IsDead(UINT BaseAddress);
	static bool IsTapped(UINT BaseAddress);
	static void Interact(UINT BaseAddress);
	static guid_t CreatedBy(UINT BaseAddress);
	static uint64_t SummonedBy(UINT BaseAddress);

	static void SetRawFacing(UINT BaseAddress, float angle);
	static float GetSideFaceRotation(UINT BaseAddress, float halfShootCone, Vector3 position);
	static bool IsFacing(UINT BaseAddress, float angle, Vector3 position);
	static bool FacePostion(UINT BaseAddress, float angle, Vector3 position);

	static int GetDynamicObjectSpellId(UINT BaseAddress);
	static int GetDynamicObjectRadius(UINT BaseAddress);
	static int GetDynamicObjectCastTime(UINT BaseAddress);
};
