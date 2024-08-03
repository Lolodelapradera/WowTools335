#include "data.h"
#include <Windows.h>
#include <detours.h>
#include "RegisteredFunc.h"
#include "MemoryController.h"

static void Lua_OpenFrameXMlApi_bulk()
{
    lua_State* L = GetLuaState();

    // Create the _A table
    lua_createtable(L, 0, 0);

    lua_createtable(L, 0, 0);
    // Create the ObjectManager table inside _A
    #pragma region ObjectManagerTable
    lua_createtable(L, 0, 0);
    CreatePlayer(L);
    CreateTarget(L);
    CreateDynamicObjects(L);
    CreateGameObjects(L);
    CreateWowUnits(L);

    lua_setfield(L, -2, "ObjectManager");
    #pragma endregion

    LuaTable(L);

    //TimerMetatable(L);

    lua_pushnumber(L, 1.0);
    lua_setfield(L, -2, "VERSION");

    lua_setfield(L, -2, "Backend");

    // Set _A as a global variable
    lua_setglobal(L, "_A");
}


static void(*Lua_OpenFrameXMLApi_orig)() = (decltype(Lua_OpenFrameXMLApi_orig))0x00530F85;
static void __declspec(naked) Lua_OpenFrameXMLApi_hk()
{
    __asm
    {
        pushad;
        pushfd;
        call Lua_OpenFrameXMlApi_bulk;
        popfd;
        popad;
        ret;
    }
}


void Lua_OpenFrameHook()
{
    MemoryController::DetourPatcher["OpenFrameXML"] = new DetourManager(0x00530F85, &(PVOID&)Lua_OpenFrameXMLApi_orig, Lua_OpenFrameXMLApi_hk);
}
