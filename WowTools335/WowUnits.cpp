#include "RegisteredFunc.h"
#include "ObjectMgr.h"
#include "UnitEntry.h"
#include "ObjectTypes.h"
#include "Helperfunctions.h"
#pragma warning(disable : 4244)

int CreateWowUnits(lua_State* L)
{
	lua_register(L, Unit_PROTO ".IsValid", [](lua_State* L)
		{
			UINT addr = lua_checkobject(L, 1, OBJECT_MT);
			lua_pushboolean(L, addr != 0);
			return 1;
		});
	lua_register(L, Unit_PROTO ".GetGuid", [](lua_State* L)
		{
			lua_pushstring(L, tohex16(GetObjGuid(lua_checkobject(L, 1, OBJECT_MT))).c_str());
			return 1;
		});
	lua_register(L, Unit_PROTO ".GetHealthPercentage", [](lua_State* L)
		{
			lua_pushnumber(L, HealthPercent(lua_checkobject(L, 1, OBJECT_MT)));
			return 1;
		});
	lua_register(L, Unit_PROTO ".GetPowerPercentage", [](lua_State* L)
		{
			lua_pushnumber(L, GetPowerPercentage(lua_checkobject(L, 1, OBJECT_MT)));
			return 1;
		});
	lua_register(L, Unit_PROTO ".GetEntryId", [](lua_State* L)
		{
			lua_pushnumber(L, GetObjectEntry(lua_checkobject(L, 1, OBJECT_MT)));
			return 1;
		});

	lua_register(L, Unit_PROTO ".GetName", [](lua_State* L)
	{
		lua_pushstring(L, ObjectMgr::GetName(lua_checkobject(L, 1, OBJECT_MT)));
		return 1;
	});

	#pragma region WowUnitCreatingTable
	lua_createtable(L, 0, 0);
	lua_getfield(L, LUA_REGISTRYINDEX, Unit_PROTO); // mt, proto
	lua_setfield(L, -2, "__index"); // mt
	lua_setfield(L, LUA_REGISTRYINDEX, OBJECT_MT); // 

	lua_registerfunction(L, -2, "GetWowUnits", [](lua_State* L)
	{
		lua_createtable(L, 0, 0);
		size_t i = 0;
		ObjectMgr::enumObjects([L, &i](guid_t guid)
		{
			auto unit = ObjectMgr::GetObjectPointer(guid, TYPEMASK_UNIT);
			if (unit != NULL)
			{
				lua_pushobject(L, unit, OBJECT_MT);
				lua_rawseti(L, -2, ++i);
			}
			return true;
		});
		return 1;
	}, Unit_PROTO);
	return 1;
#pragma endregion
}