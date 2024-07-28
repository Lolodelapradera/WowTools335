#include "RegisteredFunc.h"
#include "ObjectMgr.h"
#include "UnitEntry.h"
#include "ObjectTypes.h"
#pragma warning(disable : 4244)

int CreateGameObjects(lua_State* L)
{

	lua_register(L, GameObject_PROTO ".GetName", [=](lua_State* F)
	{
		lua_pushstring(L, ObjectMgr::GetName(lua_checkobject(L, 1, GameObject_MT)));
		return 1;
	});
	#pragma region GetGameObjectsTable
	lua_createtable(L, 0, 0);
	lua_getfield(L, LUA_REGISTRYINDEX, GameObject_PROTO); // mt, proto
	lua_setfield(L, -2, "__index"); // mt
	lua_setfield(L, LUA_REGISTRYINDEX, GameObject_MT); // 
	lua_registerfunction(L, -2, "GetGameObjects", [](lua_State* L)
		{
			lua_createtable(L, 0, 0);
			size_t i = 0;
			ObjectMgr::enumObjects([L, &i](guid_t guid)
				{
					ObjectEntry* Object = (ObjectEntry*)ObjectMgr::find(guid, TYPEMASK_GAMEOBJECT);
					if (Object)
					{
						auto ptr = ObjectMgr::GetObjectPointer(guid, TYPEMASK_GAMEOBJECT);
						lua_pushobject(L, ptr, GameObject_MT);
						lua_rawseti(L, -2, ++i);
					}
					return true;
				});
			return 1;
		}, GameObject_PROTO);
	return 1;
#pragma endregion
}