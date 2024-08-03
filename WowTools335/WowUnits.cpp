#include "RegisteredFunc.h"
#include "ObjectMgr.h"
#include "ObjectTypes.h"
#include "Vector3.h"
#include "Helperfunctions.h"

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
		lua_pushstring(L, tohex16(ObjectMgr::GetObjGuid(lua_checkobject(L, 1, OBJECT_MT))).c_str());
		return 1;
	});
	lua_register(L, Unit_PROTO ".GetHealthPercentage", [](lua_State* L)
	{
		lua_pushnumber(L, ObjectMgr::GetHealthPercent(lua_checkobject(L, 1, OBJECT_MT)));
		return 1;
	});
	lua_register(L, Unit_PROTO ".GetPowerPercentage", [](lua_State* L)
	{
		lua_pushnumber(L, ObjectMgr::GetPowerPercentage(lua_checkobject(L, 1, OBJECT_MT)));
		return 1;
	});
	lua_register(L, Unit_PROTO ".GetEntryId", [](lua_State* L)
	{
		lua_pushnumber(L, ObjectMgr::GetObjectEntry(lua_checkobject(L, 1, OBJECT_MT)));
		return 1;
	});
	lua_register(L, Unit_PROTO ".GetName", [](lua_State* L)
	{
		lua_pushstring(L, ObjectMgr::GetName(lua_checkobject(L, 1, OBJECT_MT)));
		return 1;
	});
	lua_register(L, Unit_PROTO ".GetPosition", [=](lua_State* L)
	{
		Vector3 pos = ObjectMgr::GetPosition(lua_checkobject(L, 1, OBJECT_MT));
		// Check if the position is valid (not Invalid).
		if (pos.Invalid()) return 0;

		// Push the X, Y, and Z coordinates of the position onto the Lua stack.
		lua_pushnumber(L, pos.X);
		lua_pushnumber(L, pos.Y);
		lua_pushnumber(L, pos.Z);

		// Return the number of values pushed onto the stack (3 in this case).
		return 3;
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