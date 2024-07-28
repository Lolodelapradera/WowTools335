#include "RegisteredFunc.h"
#include "ObjectMgr.h"
#include "UnitEntry.h"
#include "ObjectTypes.h"

int CreateDynamicObjects(lua_State* L)
{

	#pragma region DynamicObjectTable
	lua_createtable(L, 0, 0);
	lua_getfield(L, LUA_REGISTRYINDEX, Dynamic_PROTO); // mt, proto
	lua_setfield(L, -2, "__index"); // mt
	lua_setfield(L, LUA_REGISTRYINDEX, Dynamic_MT); // 

	lua_registerfunction(L, -2, "GetDynamicObjects", [](lua_State* L)
	{
		lua_createtable(L, 0, 0);
		size_t i = 0;
		ObjectMgr::enumObjects([L, &i](guid_t guid)
			{
				UnitEntry* DYNAMICOBJECT = (UnitEntry*)ObjectMgr::find(guid, TYPEMASK_DYNAMICOBJECT);
				if (DYNAMICOBJECT)
				{
					auto ptr = ObjectMgr::GetObjectPointer(guid, TYPEMASK_DYNAMICOBJECT);
					lua_pushobject(L, ptr, Dynamic_MT);
					lua_rawseti(L, -2, ++i);
				}
				return true;
			});
		return 1;
	}, Players_PROTO);
	return 1;
#pragma endregion
}