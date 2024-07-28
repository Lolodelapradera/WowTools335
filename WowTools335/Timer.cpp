#include "RegisteredFunc.h"
#include <iostream>
#include "TimerClass.h"



int lua_timer_start(lua_State* L)
{
	std::cout << "started" << std::endl;
	LuaTimer* timer = *(LuaTimer**)luaL_checkudata(L, 1, "timerMetatable");
	timer->start();
	return 0;
}

int lua_timer_stop(lua_State* L)
{
	LuaTimer* timer = *(LuaTimer**)luaL_checkudata(L, 1, "timerMetatable");
	timer->stop();
	return 0;
}

int lua_timer_gc(lua_State* L)
{
	LuaTimer* timer = *(LuaTimer**)luaL_checkudata(L, 1, "timerMetatable");
	timer->~LuaTimer();
	delete timer;
	return 0;
}

extern const luaL_Reg TimerMethods[]
{
	{"Start", lua_timer_start},
	{"Stop", lua_timer_stop},
	{"__gc", lua_timer_gc},
	{nullptr, nullptr}
};

int newIndex(lua_State* L)
{
	LuaTimer** timer = static_cast<LuaTimer**>(luaL_checkudata(L, 1, "timerMetatable"));
	const char* key = lua_tostring(L, 2);

	if (std::string(key) == "interval")
	{
		(*timer)->interval = lua_tonumber(L, 3);
	}
	else if (std::string(key) == "Repeat")
	{
		(*timer)->Repeat = lua_toboolean(L, 3);
	}

	return 0;
}

int CreateTimerMetatable(lua_State* L)
{
	if (!lua_isstring(L, 1))
		return 0;
	// Create a new metatable named "timerMetatable" in Lua registry
	lua_newmetatable(L, "timerMetatable", LUA_REGISTRYINDEX);


	// Set __index metamethod to point to itself
	lua_pushvalue(L, -1); // Duplicate the metatable
	lua_setfield(L, -2, "__index");
	PushMethod(L, TimerMethods);

	lua_pushcfunction(L, newIndex);
	lua_setfield(L, -2, "__newindex");


	LuaTimer* timer = new LuaTimer(lua_tostring(L, 1));

	LuaTimer** luaTimer = static_cast<LuaTimer**>(lua_newuserdata(L, sizeof(LuaTimer*)));
	*luaTimer = timer;


	luaL_getmetatable(L, "timerMetatable");
	lua_setmetatable(L, -2);



	return 1; // Return 1 to indicate that 1 value (metatable) is returned
}



//int TimerMetatable(lua_State* L)
//{
//	
//	lua_pushcfunction(L, CreateTimerMetatable);
//	lua_setfield(L, -2, "Timer");
//
//	return 1;
//}


