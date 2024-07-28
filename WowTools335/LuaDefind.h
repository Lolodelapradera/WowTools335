/**
 * @brief Represents the special return value indicating multiple return values in Lua.
 */
#define LUA_MULTRET (-1)

 /**
 * @brief Index of the Lua registry.
 *
 * The Lua registry is a table used by the interpreter to store references to Lua values.
 */
#define LUA_REGISTRYINDEX (-10000)

 /**
 * @brief Index of the environment table.
 *
 * This index refers to the environment table, typically used for global variables.
 */
#define LUA_ENVIRONINDEX (-10001)

 /**
 * @brief Index of the global table.
 *
 * This index refers to the global table in the Lua environment.
 */
#define LUA_GLOBALSINDEX (-10002)

 /**
 * @brief Macro to calculate the index of an upvalue.
 *
 * This macro calculates the index of an upvalue based on its position.
 *
 * @param i Index of the upvalue.
 */
#define lua_upvalueindex(i) (LUA_GLOBALSINDEX - (i))

 /**
 * @brief Error code indicating a yield.
 */
#define LUA_YIELD 1

 /**
 * @brief Error code indicating a runtime error.
 */
#define LUA_ERRRUN 2

 /**
 * @brief Error code indicating a syntax error.
 */
#define LUA_ERRSYNTAX 3

 /**
 * @brief Error code indicating a memory allocation error.
 */
#define LUA_ERRMEM 4

 /**
 * @brief Error code indicating an error in the error handling function.
 */
#define LUA_ERRERR 5

 /**
 * @brief Lua type representing no value.
 */
#define LUA_TNONE (-1)

 /**
 * @brief Lua type representing nil.
 */
#define LUA_TNIL 0

 /**
 * @brief Lua type representing a boolean value.
 */
#define LUA_TBOOLEAN 1

 /**
 * @brief Lua type representing light userdata.
 */
#define LUA_TLIGHTUSERDATA 2

 /**
 * @brief Lua type representing a number.
 */
#define LUA_TNUMBER 3

 /**
 * @brief Lua type representing a string.
 */
#define LUA_TSTRING 4

 /**
 * @brief Lua type representing a table.
 */
#define LUA_TTABLE 5

 /**
 * @brief Lua type representing a function.
 */
#define LUA_TFUNCTION 6

 /**
 * @brief Lua type representing userdata.
 */
#define LUA_TUSERDATA 7

 /**
 * @brief Lua type representing a thread.
 */
#define LUA_TTHREAD 8

 /**
 * @brief Special reference value indicating no reference.
 */
#define LUA_NOREF (-2)

 /**
 * @brief Special reference value indicating a reference to nil.
 */
#define LUA_REFNIL (-1)

 /**
 * @brief Sets a global variable in the Lua environment.
 *
 * This macro sets a global variable in the Lua environment using a given name.
 *
 * @param L Pointer to the Lua state.
 * @param s Name of the global variable.
 */
#define lua_setglobal(L, s) lua_setfield(L, LUA_GLOBALSINDEX, (s))

 /**
 * @brief Retrieves a global variable from the Lua environment.
 *
 * This macro retrieves a global variable from the Lua environment using a given name.
 *
 * @param L Pointer to the Lua state.
 * @param s Name of the global variable.
 */
#define lua_getglobal(L, s) lua_getfield(L, LUA_GLOBALSINDEX, (s))

 /**
 * @brief Sets a local variable in the Lua registry.
 *
 * This macro sets a local variable in the Lua registry using a given name.
 *
 * @param L Pointer to the Lua state.
 * @param s Name of the local variable.
 */
#define lua_setLocal(L, s) lua_setfield(L, LUA_REGISTRYINDEX, (s))

 /**
 * @brief Retrieves a local variable from the Lua registry.
 *
 * This macro retrieves a local variable from the Lua registry using a given name.
 *
 * @param L Pointer to the Lua state.
 * @param s Name of the local variable.
 */
#define lua_getLocal(L, s) lua_getfield(L, LUA_REGISTRYINDEX, (s))

 /**
 * @brief Macro to check if a Lua value at index n is of type light userdata.
 *
 * This macro checks if the Lua value at the specified index is of type light userdata.
 *
 * @param L Pointer to the Lua state.
 * @param n Index of the value on the stack.
 */
#define lua_islightuserdata(L, n) (lua_type(L, (n)) == LUA_TLIGHTUSERDATA)

 /**
 * @brief Macro to push a C function onto the Lua stack.
 *
 * This macro pushes a C function onto the Lua stack as a closure.
 *
 * @param L Pointer to the Lua state.
 * @param f Pointer to the C function.
 */
#define lua_pushcfunction(L, f) lua_pushcclosure(L, (f), 0)

 /**
 * @brief Macro to check if a Lua value at index n is of type table.
 *
 * This macro checks if the Lua value at the specified index is of type table.
 *
 * @param L Pointer to the Lua state.
 * @param n Index of the value on the stack.
 */
#define lua_istable(L, n) (lua_type(L, (n)) == LUA_TTABLE)



 /**
 * @brief Macro to remove elements from the Lua stack.
 *
 * This macro removes n elements from the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param n Number of elements to remove.
 */
#define lua_pop(L, n) lua_settop(L, -(n)-1)

 /**
 * @brief Macro to check if a Lua value at index n is nil.
 *
 * This macro checks if the Lua value at the specified index is nil.
 *
 * @param L Pointer to the Lua state.
 * @param n Index of the value on the stack.
 */
#define lua_isnil(L, n) (lua_type(L, (n)) == LUA_TNIL)

 /**
 * @brief Macro to check if a Lua value at index n is nil or absent.
 *
 * This macro checks if the Lua value at the specified index is nil or absent.
 *
 * @param L Pointer to the Lua state.
 * @param n Index of the value on the stack.
 */
#define lua_isnoneornil(L, n) (lua_type(L, (n)) <= 0)

 /**
 * @brief Macro to register a C function as a global variable.
 *
 * This macro registers a C function as a global variable in the Lua environment.
 *
 * @param l Pointer to the Lua state.
 * @param n Name of the global variable.
 * @param s Name of the global variable.
 */
#define lua_Register(l,n,s) (lua_pushcfunction(l,n), lua_setglobal(l,s))

 /**
 * @brief Macro to retrieve a metatable from the Lua registry.
 *
 * This macro retrieves a metatable from the Lua registry using the specified name.
 *
 * @param L Pointer to the Lua state.
 * @param n Name of the metatable.
 */
#define luaL_getmetatable(L,n)  (lua_getfield(L, LUA_REGISTRYINDEX, (n)))

 /**
 * @brief Macro to create a new empty table.
 *
 * This macro creates a new empty table and pushes it onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 */
#define lua_newtable(L) (lua_createtable(L,0,0))



 /**
 * @brief Macro to push a string literal onto the Lua stack.
 *
 * This macro pushes a string literal onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param s String literal.
 */
#define lua_pushliteral(L, s)	\
	lua_pushstring(L, "" s, (sizeof(s)/sizeof(char))-1)
