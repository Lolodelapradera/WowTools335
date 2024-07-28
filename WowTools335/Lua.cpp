
#include "Lua.h"
#include <iostream>
#include <vector>


inline lua_State* GetLuaState()
{
    return ((decltype(&GetLuaState))0x00817DB0)();
}

inline void lua_execute(const char* text)
{

    ((void(__cdecl*)(const char*, const char*, void*))0x00819210)(text, "\0", nullptr);
}

inline char* lua_tostring(lua_State* state, int n_param)
{

    return ((char* (__cdecl*)(lua_State*, int, int))0x0084E0E0)(state, n_param, 0);
}

inline int lua_pushnil(lua_State* state)
{

    return ((int(__cdecl*)(lua_State*))0x0084E280)(state);
}

inline void lua_pushcclosure(lua_State* L, lua_CFunction fn, int n)
{

    return ((decltype(&lua_pushcclosure))0x0084E400)(L, fn, n);
}


inline void lua_setfield(lua_State* L, int idx, const char* key)
{

    return ((decltype(&lua_setfield))0x0084E900)(L, idx, key);
}


inline void lua_pushstring(lua_State* L, const char* val)
{

    return ((decltype(&lua_pushstring))0x0084E350)(L, val);
}


inline double lua_tonumber(lua_State* L, int idx)
{

    return ((double(__cdecl*)(lua_State*, int))0x0084E030)(L, idx);
}



inline void lua_pushboolean(lua_State* L, bool val)
{
    return ((decltype(&lua_pushboolean))0x0084E4D0)(L, val);
}


inline void lua_pushnumber(lua_State* L, double val)
{
    return ((decltype(&lua_pushnumber))0x0084E2A0)(L, val);
}


inline void lua_pushinteger(lua_State* L, int val)
{
    return ((decltype(&lua_pushinteger))0x0084E2D0)(L, val);
}


inline int lua_isstring(lua_State* L, int idx)
{
    return ((decltype(&lua_isstring))0x0084DF60)(L, idx);
}


inline int lua_tointeger(lua_State* L, int idx)
{
    return ((decltype(&lua_tointeger))0x0084E070)(L, idx);
}


inline void lua_createtable(lua_State* L, int narray, int nrec)
{
    return ((decltype(&lua_createtable))0x0084E6E0)(L, narray, nrec);
}

inline void lua_pushlightuserdata(lua_State* L, void* p)
{
    return ((decltype(&lua_pushlightuserdata))0x0084E500)(L, p);
}

inline int lua_ref(lua_State* L, int t)
{
    return ((decltype(&lua_ref))0x0084F6C0)(L, t);
}
inline void luaL_unref(lua_State* L, int t, int ref) { return ((decltype(&luaL_unref))0x0084F7A0)(L, t, ref); }



inline int lua_settable(lua_State* L, int number)
{
    return ((int(__cdecl*)(lua_State*, int))0x0084E8D0)(L, number);
}


inline int lua_gettop(lua_State* L)
{
    return ((decltype(&lua_gettop))0x0084DBD0)(L);
}


inline void* lua_newuserdata(lua_State* L, size_t size)
{
    return ((decltype(&lua_newuserdata))0x0084F0F0)(L, size);
}


inline int lua_getfield(lua_State* L, int a1, const char* a2)
{
    return ((int(__cdecl*)(lua_State*, int, const char*))0x84E590)(L, a1, a2);
}


inline void lua_settop(lua_State* L, int a1)
{
    ((void(__cdecl*)(lua_State*, int))0x84DBF0)(L, a1);
}


inline void lua_pushvalue(lua_State* L, int a1)
{
    ((void(__cdecl*)(lua_State*, int))0x84DE50)(L, a1);
}


inline int lua_touserdata(lua_State* L, int a1)
{
    return ((int(__cdecl*)(lua_State*, int))0x84e210)(L, a1);
}


inline int lua_setmetatable(lua_State* L, int a1)
{
    return ((int(__cdecl*)(lua_State*, int))0x84EA90)(L, a1);
}

inline int lua_error(lua_State* L, const char* format, ...)
{
    return ((decltype(&lua_error))0x0084F280)(L, format);
}


inline int lua_type(lua_State* L, int a1)
{
    return ((int(__cdecl*)(lua_State*, int))0x84DEB0)(L, a1);
}

inline void lua_rawseti(lua_State* L, int idx, int n)
{
    return ((decltype(&lua_rawseti))0x0084EA00)(L, idx, n);
}

inline void lua_rawget(lua_State* L, int idx)
{
    return ((decltype(&lua_rawget))0x0084E600)(L, idx);
}

inline int lua_getmetatable(lua_State* L, int idx)
{
    return ((decltype(&lua_getmetatable))0x0084E730)(L, idx);
}
inline int lua_rawequal(lua_State* L, int idx1, int idx2)
{
    return ((decltype(&lua_rawequal))0x0084DF90)(L, idx1, idx2);
}

inline void lua_rawgeti(lua_State* L, int idx, int n)
{
    return ((decltype(&lua_rawgeti))0x0084E670)(L, idx, n);
}

inline int lua_SetRow(lua_State* state, int RowNumber)
{
    return ((int(__cdecl*)(lua_State*, int))0x0084DAB0)(state, RowNumber);
}

inline bool lua_IsNumber(lua_State* state, int n_param)
{
    return ((bool(__cdecl*)(lua_State*, int))0x0084DF20)(state, n_param);
}

inline bool lua_toboolean(lua_State* L, int idx)
{
    return ((decltype(&lua_toboolean))0x0084E0B0)(L, idx);
}


void* luaL_checkudata(lua_State* L, int index, const char* tname) {
    int udValue = lua_touserdata(L, index);
    void* ud = reinterpret_cast<void*>(udValue);
    if (ud != NULL) {
        if (lua_getmetatable(L, index)) {
            lua_getfield(L, LUA_REGISTRYINDEX, tname);
            if (lua_rawequal(L, -1, -2)) {
                lua_pop(L, 2);
                return ud;
            }

            lua_pop(L, 2);
        }
    }
    lua_error(L, "userdata expected", index);
    return NULL;
}


void PushFuncToTable(lua_State* L, char* TableName, const luaL_Reg regfunc[])
{
    lua_createtable(L, 0, 0);
    for (int i = 0; regfunc[i].name != nullptr && regfunc[i].func != nullptr; ++i)
    {

        lua_pushcfunction(L, regfunc[i].func);

        lua_setfield(L, -2, regfunc[i].name);
    }
    lua_setglobal(L, TableName);
}




void PushFunc(lua_State* L, const luaL_Reg regfunc[])
{

    for (int i = 0; regfunc[i].name != nullptr && regfunc[i].func != nullptr; ++i)
    {

        lua_pushcfunction(L, regfunc[i].func);


        lua_setglobal(L, regfunc[i].name);

    }
}

void PushMethod(lua_State* L, const luaL_Reg regfunc[])
{

    for (int i = 0; regfunc[i].name != nullptr && regfunc[i].func != nullptr; ++i)
    {

        lua_pushcfunction(L, regfunc[i].func);

        lua_setfield(L, -2, regfunc[i].name);

        /*lua_pushstring(L, regfunc[i].name);
        lua_pushcfunction(L, regfunc[i].func);
        lua_settable(L, -3);*/
    }
}



int lua_newmetatable(lua_State* L,const char* tname, int Index)
{
    lua_getfield(L, Index, tname);  /* get registry.name */
    if (!lua_isnil(L, -1))  /* name already in use? */
    {
        return 0;  /* leave previous value on top, but return 0 */
    }
    lua_pop(L, 1);
    lua_createtable(L, 0, 0);  /* create metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, Index, tname);  /* registry.name = metatable */
    return 1;
}


inline int __cdecl lua_loadbuffer(lua_State* state, const char* a2, unsigned int a3, const char* a4)
{
    return ((int(__cdecl*)(lua_State*, const char*, unsigned int, const char*))0x0084F860)(state, a2, a3, a4);
}


inline int lua_pcall(lua_State* L, int NUM_Args, int NUM_RETURNS, int a4 = 0)
{
    return ((int(__cdecl*)(lua_State*, int, int, int))0x0084EC50)(L, NUM_Args, NUM_RETURNS, a4);
}


inline int lua_next(lua_State* L, int idx)
{
    return ((decltype(&lua_next))0x0084EF50)(L, idx);
}


int lua_setfenv(lua_State* L, int idx)
{
    return ((int(__cdecl*)(lua_State*, int))0x0084EC50)(L, idx);
}

int lua_createmetatable(lua_State* L, const char* Name, const luaL_Reg regfunc[], int index)
{
    lua_newmetatable(L, Name, index);
    PushMethod(L, regfunc);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);
    return 1;
}

void DumpRegistry(lua_State* L, int idx)
{
    lua_pushnil(L);  // Start iterating from nil
    while (lua_next(L, idx) != 0)
    {
        // Key is at index -2, value is at index -1
        const char* key = lua_tostring(L, -2);
        if (key)
            printf("%s\n", key);
        else
            printf("[NULL]\n");

        lua_pop(L, 1);
    }
}

int DumpLuaStack(lua_State* L)
{
    int numArgs = lua_gettop(L); // Get the number of arguments on the stack

    printf("Number of arguments: %d\n", numArgs);

    for (int i = 1; i <= numArgs; ++i) {
        printf("Argument %d: ", i);

        int type = lua_type(L, i);
        switch (type) {
        case LUA_TNIL:
            printf("nil");
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%f", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("%s", lua_tostring(L, i));
            break;
        case LUA_TTABLE:
            printf("table");
            break;
        case LUA_TFUNCTION:
            printf("function");
            break;
        case LUA_TUSERDATA:
            printf("userdata");
            break;
        case LUA_TTHREAD:
            printf("thread");
            break;
        case LUA_TLIGHTUSERDATA:
            printf("lightuserdata");
            break;
        default:
            printf("unknown");
            break;
        }

        // Print the value if applicable
        if (type == LUA_TSTRING || type == LUA_TNUMBER || type == LUA_TBOOLEAN) {
            printf(" (value: ");
            if (type == LUA_TSTRING)
                printf("%s", lua_tostring(L, i));
            else if (type == LUA_TNUMBER)
                printf("%f", lua_tonumber(L, i));
            else if (type == LUA_TBOOLEAN)
                printf(lua_toboolean(L, i) ? "true" : "false");
            printf(")");
        }

        printf("\n");
    }

    // Rest of your function...

    return 1;
}

inline void lua_remove(lua_State* L, int idx)
{
    return ((decltype(&lua_remove))0x0084DC50)(L, idx); 
}


inline void lua_gettable(lua_State* L, int idx) 
{ 
    return ((decltype(&lua_gettable))0x0084E560)(L, idx);
}

void lua_setpath(lua_State* L, int registry, const char* path)
{
    if (lua_gettop(L) == 0) return;
    std::vector<std::string> words;
    std::stringstream ss(path);
    std::string item;
    while (std::getline(ss, item, '.'))
    {
        words.push_back(item);
    }


    if (words.empty()) return;
    if (words.size() == 1) return lua_setfield(L, registry, path);

    std::string tmpStr(words.front());
    std::cout << tmpStr << std::endl;
    lua_getfield(L, registry, tmpStr.c_str()); // val, tbl
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1); // val
        lua_createtable(L, 0, 0); // val, tbl
        lua_pushvalue(L, -1); // val, tbl, tbl
        lua_setfield(L, registry, tmpStr.c_str()); // val, tbl
    }

    for (size_t i = 1; i < words.size() - 1; ++i) {
        tmpStr = words[i];
        lua_getfield(L, -1, tmpStr.c_str());
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_createtable(L, 0, 0);
            lua_setfield(L, -2, tmpStr.c_str());
        }
    }

    tmpStr = words.back();
    lua_pushvalue(L, -2); // val, tbl, val
    lua_setfield(L, -2, tmpStr.c_str()); // val, tbl
    lua_pop(L, 2); //
}

using lua_CppFunction = std::function<int(lua_State*)>;
void lua_pushcppfunction(lua_State* L, lua_CppFunction func, const char* txt);
static int lua_functionWrapper_gc(lua_State* L)
{
    lua_CppFunction* func = (lua_CppFunction*)lua_touserdata(L, 1);
    func->~lua_CppFunction();
    return 0;
}

void lua_pushcppfunction(lua_State* L, lua_CppFunction func, const char* txt)
{
    lua_CppFunction* ptr = (lua_CppFunction*)lua_newuserdata(L, sizeof(lua_CppFunction)); // func
    new (ptr) lua_CppFunction(std::move(func));

    lua_getfield(L, LUA_REGISTRYINDEX, txt); // func, mt
    if (lua_type(L, -1) != LUA_TTABLE) {
        lua_pop(L, 1); // func
        lua_createtable(L, 0, 0); // func, mt
        lua_pushcclosure(L, lua_functionWrapper_gc, 0);
        lua_setfield(L, -2, "__gc");
        lua_pushboolean(L, false);
        lua_setfield(L, -2, "__metatable");
        lua_pushvalue(L, -1); // func, mt, mt
        lua_setfield(L, LUA_REGISTRYINDEX, txt); // func, mt
    }
    lua_setmetatable(L, -2); // func

    // Wrap the function with an error handler
    auto wrapper = [](lua_State* L) -> int {
        lua_CppFunction* func = (lua_CppFunction*)lua_touserdata(L, lua_upvalueindex(1));
        try {
            return (*func)(L);
        }
        catch (const std::exception& e) {
            lua_error(L, "C++ exception caught: %s", e.what());
        }
        catch (...) {
            lua_error(L, "Unknown C++ exception caught");
        }
        return 0;
        };
    lua_pushcclosure(L, wrapper, 1); // wrap
}

inline void lua_registerfunction(lua_State* L, int registry, const char* path, lua_CppFunction func, const char* text)
{
    lua_pushcppfunction(L, std::move(func), text);
    lua_setpath(L, registry, path);

}

inline void lua_register(lua_State* L, const char* path, lua_CppFunction func)
{
    lua_pushcppfunction(L, std::move(func), path);
    lua_setpath(L, LUA_REGISTRYINDEX, path);
}

void lua_pushobject(lua_State* L, uint64_t guid, const char* Field)
{
    lua_createtable(L, 0, 0); // tbl
    uint64_t* ptr = (uint64_t*)lua_newuserdata(L, sizeof(uint64_t)); // tbl, udata
    *ptr = guid;
    lua_rawseti(L, -2, -1); // tbl
    lua_getfield(L, LUA_REGISTRYINDEX, Field); // tbl, mt
    lua_setmetatable(L, -2); // tbl
}

uint64_t lua_checkobject(lua_State* L, int pos, const char* Field)
{
    if (!lua_istable(L, pos) || !lua_getmetatable(L, pos))
    {
        return 0;
    }

    lua_getfield(L, LUA_REGISTRYINDEX, Field); // mt, mt
    bool isSame = lua_rawequal(L, -1, -2);
    lua_pop(L, 2);
    if (!isSame)
        return 0;
    lua_rawgeti(L, pos, -1); // 0
    uint64_t* ptr = (uint64_t*)lua_touserdata(L, -1);
    lua_pop(L, 1);
    return *ptr;
};