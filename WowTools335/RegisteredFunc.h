#pragma once
#include "Lua.h"
#define WIN32_LEAN_AND_MEAN  

#define Player_PROTO "PlayerProto"
#define Player_MT "PlayerMT"

#define Target_PROTO "TargetProto"
#define Target_MT "TargetMT"

#define GameObject_PROTO "GameObjectProto"
#define GameObject_MT "GameObjectMT"

#define Unit_PROTO "WowUnit"
#define OBJECT_MT "ObjectMt"

#define Party_PROTO "PartyProto"
#define Party_MT "PartyMT"

#define Players_PROTO "PlayersProto"
#define Players_MT "PlayersMT"

#define Dynamic_PROTO "DynamicProto"
#define Dynamic_MT "DynamicMT"

std::vector<std::string> CallBack;
int TimerMetatable(lua_State* L);

int LuaTable(lua_State* L);
int CreatePlayer(lua_State* L);
int CreateTarget(lua_State* L);
int CreateDynamicObjects(lua_State* L);
int CreateGameObjects(lua_State* L);
int CreateWowUnits(lua_State* L);
