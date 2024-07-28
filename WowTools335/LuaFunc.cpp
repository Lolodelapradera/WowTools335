#include "RegisteredFunc.h"

int LuaExecute(lua_State* L)
{
	if (lua_isstring(L, 1))
		lua_execute(lua_tostring(L, 1));

	return 0;
}


int LuaTable(lua_State* L)
{
	lua_createtable(L, 0, 0);

	lua_pushcfunction(L, LuaExecute);
	lua_setfield(L, -2, "Execute");

	lua_setfield(L, -2, "Lua");
	return 1;
}