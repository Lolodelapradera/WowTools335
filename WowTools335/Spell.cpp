#include "RegisteredFunc.h"

int CreateSpell(lua_State* L)
{


#pragma region MyRegion
	lua_createtable(L, 0, 0);
	lua_getfield(L, LUA_REGISTRYINDEX, Spell_PROTO);
	lua_setfield(L, -2, "__index");
	lua_createtable(L, 0, 0);
	lua_pushcppfunction(L, [](lua_State* L)
	{
		int* ptr = (int*)lua_touserdata(L, 1);
		ptr = int();
		return 0;
	}, Spell_MT);

	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	lua_setfield(L, LUA_REGISTRYINDEX, Spell_MT);

	lua_registerfunction(L, -2, "Spell", [](lua_State* L)
	{
		if(lua_type(L, 1) == LUA_TSTRING)


		lua_createtable(L, 0, 0);
		int* ptr = (int*)lua_newuserdata(L, sizeof(int));
		*ptr = static_cast<int>(lua_tonumber(L, 1));

		lua_rawseti(L, -2, 0);
		lua_getfield(L, LUA_REGISTRYINDEX, Spell_MT);
		lua_setmetatable(L, -2);
		return 1;
	}, Spell_MT);
	return 1;
#pragma endregion
}