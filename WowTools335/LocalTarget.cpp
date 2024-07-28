#include "RegisteredFunc.h"
#include "ObjectMgr.h"
#pragma warning(disable : 4244)

int CreateTarget(lua_State* L)
{

	#pragma region MyRegion
	lua_createtable(L, 0, 0);
	lua_getfield(L, LUA_REGISTRYINDEX, Target_PROTO);
	lua_setfield(L, -2, "__index");
	lua_createtable(L, 0, 0);
	lua_pushcppfunction(L, [](lua_State* L)
	{
		int* ptr = (int*)lua_touserdata(L, 1);
		ptr = int();
		return 0;
	}, Target_MT);

	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	lua_setfield(L, LUA_REGISTRYINDEX, Target_MT);

	lua_registerfunction(L, -2, "GetTarget", [](lua_State* L)
		{
			lua_createtable(L, 0, 0);
			int* ptr = (int*)lua_newuserdata(L, sizeof(int));
			new (ptr) int();
			lua_rawseti(L, -2, 0);
			lua_getfield(L, LUA_REGISTRYINDEX, Target_MT);
			lua_setmetatable(L, -2);
			return 1;
		}, Target_MT);
	return 1;
#pragma endregion
}