#include "Warden.h"
#include <iostream>
#include "WardenHelpers.h"

Warden::LuaExecute Warden::OrignalLua_String_Check = (Warden::LuaExecute)0x00819210;
int __cdecl Warden::Lua_String_Check(const char* str, int a2, int a3)
{
	if (!tContains(str, "SendAddonMessage") || tContains(str, "ClearTarget=function()"))
		return OrignalLua_String_Check(str, a2, a3);

	if (tContains(str, "MACRO_ACTION_FORBIDDEN"))
		str = "return false";

	//printf("[Warden] Lua String Check = %s\n", str);

	Loggin(true, "Warden_Scans.txt", "[Warden] Lua String Check = %s\n", str);


	return OrignalLua_String_Check(str, a2, a3);
}
