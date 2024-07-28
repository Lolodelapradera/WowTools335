#pragma once
#include <string>
#include <functional>
#include "LuaDefind.h"
#include <sstream>
#include <variant>

/**
 * @brief Forward declaration of the Lua state structure.
 */
struct lua_State;

/**
 * @brief Retrieves the Lua state pointer.
 *
 * This function returns a pointer to the Lua state.
 *
 * @return lua_State* Pointer to the Lua state.
 */
inline lua_State* GetLuaState();

/**
 * @brief Definition of a Lua C function pointer type.
 */
using lua_CFunction = int(*)(lua_State*);

using lua_CppFunction = std::function<int(lua_State*)>;

/**
 * @brief Structure representing a Lua/LuaJIT registry entry.
 */
typedef struct luaL_Reg
{
    const char* name;   /**< Name of the function. */
    lua_CFunction func; /**< Pointer to the C function implementing the Lua function. */
} luaL_Reg;


/**
 * @brief Executes a Lua script provided as text.
 *
 * This function executes a Lua script provided as text.
 *
 * @param text The Lua script to execute.
 */
inline void lua_execute(const char* text);


/**
 * @brief Converts a Lua value at the given stack index to a string.
 *
 * This function converts a Lua value at the given stack index to a string.
 *
 * @param state Pointer to the Lua state.
 * @param n_param Index of the Lua value on the stack.
 * @return char* Pointer to the converted string.
 */
inline char* lua_tostring(lua_State* state, int n_param);

/**
 * @brief Pushes a nil value onto the Lua stack.
 *
 * This function pushes a nil value onto the Lua stack.
 *
 * @param state Pointer to the Lua state.
 * @return int The number of elements on the stack after the operation.
 */
inline int lua_pushnil(lua_State* state);

/**
 * @brief Pushes a C function onto the Lua stack as a closure.
 *
 * This function pushes a C function onto the Lua stack as a closure.
 *
 * @param L Pointer to the Lua state.
 * @param fn Pointer to the C function.
 * @param n Number of values to be closed.
 */
inline void lua_pushcclosure(lua_State* L, lua_CFunction fn, int n);

/**
 * @brief Sets the value at the top of the stack as the value of the field of the table at the given index.
 *
 * This function sets the value at the top of the stack as the value of the field of the table at the given index.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the table on the stack.
 * @param key Name of the field to set.
 */
inline void lua_setfield(lua_State* L, int idx, const char* key);

/**
 * @brief Pushes a string onto the Lua stack.
 *
 * This function pushes a string onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param val The string value to push.
 */
inline void lua_pushstring(lua_State* L, const char* val);

/**
 * @brief Converts the Lua value at the given stack index to a double-precision floating point number.
 *
 * This function converts the Lua value at the given stack index to a double-precision floating point number.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the Lua value on the stack.
 * @return double The converted number.
 */
inline double lua_tonumber(lua_State* L, int idx);

/**
 * @brief Pushes a boolean value onto the Lua stack.
 *
 * This function pushes a boolean value onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param val The boolean value to push.
 */
inline void lua_pushboolean(lua_State* L, bool val);

/**
 * @brief Pushes a number onto the Lua stack.
 *
 * This function pushes a number onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param val The number to push.
 */
inline void lua_pushnumber(lua_State* L, double val);

/**
 * @brief Pushes an integer onto the Lua stack.
 *
 * This function pushes an integer onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param val The integer to push.
 */
inline void lua_pushinteger(lua_State* L, int val);
/**
 * @brief Checks if the value at the given index is a string.
 *
 * This function checks if the value at the given index in the Lua stack is a string.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the value on the stack.
 * @return int Returns 1 if the value is a string, 0 otherwise.
 */
inline int lua_isstring(lua_State* L, int idx);

/**
 * @brief Converts the Lua value at the given index to an integer.
 *
 * This function converts the Lua value at the given index to an integer.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the value on the stack.
 * @return int The converted integer value.
 */
inline int lua_tointeger(lua_State* L, int idx);

/**
 * @brief Creates a new empty table and pushes it onto the Lua stack.
 *
 * This function creates a new empty table and pushes it onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param narray Number of array elements pre-allocated.
 * @param nrec Number of non-array elements pre-allocated.
 */
inline void lua_createtable(lua_State* L, int narray, int nrec);

/**
 * @brief Sets the value at the given stack index as the value of the table at the given index.
 *
 * This function sets the value at the given stack index as the value of the table at the given index.
 *
 * @param L Pointer to the Lua state.
 * @param number Index of the table on the stack.
 * @return int Returns 0 on success, or an error code otherwise.
 */
inline int lua_settable(lua_State* L, int number);

/**
 * @brief Returns the number of elements on the Lua stack.
 *
 * This function returns the number of elements on the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @return int Number of elements on the stack.
 */
inline int lua_gettop(lua_State* L);

/**
 * @brief Creates a new userdata and pushes it onto the Lua stack.
 *
 * This function creates a new userdata with the specified size and pushes it onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param size Size of the userdata to allocate.
 * @return void* Pointer to the allocated userdata.
 */
inline void* lua_newuserdata(lua_State* L, size_t size);

/**
 * @brief Gets a value from a table and pushes it onto the Lua stack.
 *
 * This function gets a value from a table at the specified index and pushes it onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param a1 Index of the table.
 * @param a2 Name of the field.
 * @return int Returns the type of the retrieved value.
 */
inline int lua_getfield(lua_State* L, int a1, const char* a2);

/**
 * @brief Returns the type of the Lua value at the specified index.
 *
 * This function returns the type of the Lua value at the specified index on the stack.
 *
 * @param L Pointer to the Lua state.
 * @param a1 Index of the value on the stack.
 * @return int Type of the Lua value.
 */
inline int lua_type(lua_State* L, int a1);

/**
 * @brief Sets the stack top to the specified index.
 *
 * This function sets the stack top to the specified index.
 *
 * @param L Pointer to the Lua state.
 * @param a1 New top index for the stack.
 */
inline void lua_settop(lua_State* L, int a1);

/**
 * @brief Pushes a copy of the value at the specified index onto the stack.
 *
 * This function pushes a copy of the value at the specified index onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param a1 Index of the value to push.
 */
inline void lua_pushvalue(lua_State* L, int a1);

/**
 * @brief Converts the Lua value at the specified index to a userdata.
 *
 * This function converts the Lua value at the specified index to a userdata.
 *
 * @param L Pointer to the Lua state.
 * @param a1 Index of the value on the stack.
 * @return int The converted userdata.
 */
inline int lua_touserdata(lua_State* L, int a1);

/**
 * @brief Sets the metatable of the userdata at the specified index.
 *
 * This function sets the metatable of the userdata at the specified index.
 *
 * @param L Pointer to the Lua state.
 * @param a1 Index of the userdata on the stack.
 * @return int Returns 1 if successful, 0 otherwise.
 */
inline int lua_setmetatable(lua_State* L, int a1);

/**
 * @brief Raises an error with a formatted error message.
 *
 * This function raises an error with a formatted error message.
 *
 * @param L Pointer to the Lua state.
 * @param format Format string for the error message.
 * @return int Always returns 0.
 */
inline int lua_error(lua_State* L, const char* format, ...);

/**
 * @brief Sets the value at the given index as the value of the array part of the table at the given index.
 *
 * This function sets the value at the given index as the value of the array part of the table at the given index.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the table on the stack.
 * @param n The array index.
 */
inline void lua_rawseti(lua_State* L, int idx, int n);

/**
 * @brief Retrieves a value from the table at the given index without invoking metamethods.
 *
 * This function retrieves a value from the table at the given index without invoking metamethods.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the table on the stack.
 */
inline void lua_rawget(lua_State* L, int idx);

/**
 * @brief Pushes the metatable of the value at the given index onto the stack.
 *
 * This function pushes the metatable of the value at the given index onto the stack.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the value on the stack.
 * @return int Returns 0 if the value does not have a metatable.
 */
inline int lua_getmetatable(lua_State* L, int idx);

/**
 * @brief Checks whether the values at the given indices are equal without invoking metamethods.
 *
 * This function checks whether the values at the given indices are equal without invoking metamethods.
 *
 * @param L Pointer to the Lua state.
 * @param idx1 Index of the first value on the stack.
 * @param idx2 Index of the second value on the stack.
 * @return int Returns 1 if the values are equal, 0 otherwise.
 */
inline int lua_rawequal(lua_State* L, int idx1, int idx2);

/**
 * @brief Retrieves a value from the table at the given index with a non-numeric key.
 *
 * This function retrieves a value from the table at the given index with a non-numeric key.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the table on the stack.
 * @param n The key index.
 */
inline void lua_rawgeti(lua_State* L, int idx, int n);

/**
 * @brief Sets the stack top to the given index, allowing to remove elements from the stack.
 *
 * This function sets the stack top to the given index, allowing to remove elements from the stack.
 *
 * @param state Pointer to the Lua state.
 * @param RowNumber New stack top index.
 * @return int Always returns 0.
 */
inline int lua_SetRow(lua_State* state, int RowNumber);

/**
 * @brief Checks if the value at the specified index is a number.
 *
 * This function checks if the value at the specified index is a number.
 *
 * @param state Pointer to the Lua state.
 * @param n_param Index of the value on the stack.
 * @return bool Returns true if the value is a number, false otherwise.
 */
inline bool lua_IsNumber(lua_State* state, int n_param);

/**
 * @brief Converts the Lua value at the given index to a boolean value.
 *
 * This function converts the Lua value at the given index to a boolean value.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the value on the stack.
 * @return bool The converted boolean value.
 */
inline bool lua_toboolean(lua_State* L, int idx);

/**
 * @brief Loads and executes a Lua chunk from a buffer.
 *
 * This function loads and executes a Lua chunk from the given buffer.
 *
 * @param state Pointer to the Lua state.
 * @param a2 Pointer to the buffer containing the Lua chunk.
 * @param a3 Size of the buffer.
 * @param a4 Name associated with the chunk (used for error messages).
 * @return int Returns 0 if the chunk is successfully loaded and executed, or an error code otherwise.
 */
inline int __cdecl lua_loadbuffer(lua_State* state, const char* a2, unsigned int a3, const char* a4);


inline void lua_gettable(lua_State* L, int idx);
/**
 * @brief Simulates the behavior of Lua's lua_pcall function.
 *
 * This function is an inline wrapper for the lua_pcall function.
 *
 * @param L Pointer to the Lua state.
 * @param NUM_Args Number of arguments to pass to the Lua function.
 * @param NUM_RETURNS Number of return values expected from the Lua function.
 * @param a4 Optional argument (defaults to 0).
 * @return char* Pointer to a message or status from lua_pcall.
 */
inline int lua_pcall(lua_State* state, int a2, int a3, int a4);
/**
 * @brief Retrieves the next key-value pair from a table.
 *
 * This function retrieves the next key-value pair from the table at the given index, and pushes the key and value onto the stack.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the table on the stack.
 * @return int Returns 1 if a key-value pair is found, 0 if there are no more pairs, or -1 if the stack index is not a table.
 */
inline int lua_next(lua_State* L, int idx);



/**
 * @brief Dumps the contents of the Lua registry.
 *
 * This function dumps the contents of the Lua registry for debugging purposes.
 *
 * @param L Pointer to the Lua state.
 */
void DumpRegistry(lua_State* L);

/**
 * @brief Creates a new metatable and pushes it onto the Lua stack.
 *
 * This function creates a new metatable with the given name and pushes it onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param tname Name of the metatable.
 * @param r Number of extra table slots to preallocate.
 * @return int Returns 1 if the metatable is successfully created and pushed onto the stack, 0 otherwise.
 */
int lua_newmetatable(lua_State* L, const char* tname, int r);

/**
 * @brief Sets the environment of the value at the specified index.
 *
 * This function sets the environment of the value at the specified index.
 *
 * @param L Pointer to the Lua state.
 * @param idx Index of the value on the stack.
 * @return int Returns 1 if successful, 0 otherwise.
 */
int lua_setfenv(lua_State* L, int idx);

/**
 * @brief Checks and returns the userdata at the specified index.
 *
 * This function checks and returns the userdata at the specified index.
 *
 * @param L Pointer to the Lua state.
 * @param index Index of the userdata on the stack.
 * @param tname Name of the userdata type.
 * @return void* Pointer to the userdata.
 */
void* luaL_checkudata(lua_State* L, int index, const char* tname);

/**
 * @brief Pushes a list of methods onto the Lua stack.
 *
 * This function pushes a list of methods onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param regfunc Array of luaL_Reg structures containing method information.
 */
void PushMethod(lua_State* L, const luaL_Reg regfunc[]);

/**
 * @brief Pushes a light userdata onto the Lua stack.
 *
 * This function pushes a light userdata onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param p Pointer to the userdata.
 */
void lua_pushlightuserdata(lua_State* L, void* p);

/**
 * @brief Creates a reference to a Lua value.
 *
 * This function creates a reference to a Lua value.
 *
 * @param L Pointer to the Lua state.
 * @param t Table index where the value resides.
 * @return int Reference to the Lua value.
 */
inline int lua_ref(lua_State* L, int t);

/**
 * @brief Releases a reference to a Lua value.
 *
 * This function releases a reference to a Lua value.
 *
 * @param L Pointer to the Lua state.
 * @param t Table index where the value resides.
 * @param ref Reference to the Lua value.
 */
inline void luaL_unref(lua_State* L, int t, int ref);

/**
 * @brief Creates a metatable with specified methods and registers it.
 *
 * This function creates a metatable with specified methods and registers it.
 *
 * @param L Pointer to the Lua state.
 * @param Name Name of the metatable.
 * @param regfunc Array of luaL_Reg structures containing method information.
 * @param i Number of extra table slots to preallocate.
 * @return int Returns 1 if successful, 0 otherwise.
 */
int lua_createmetatable(lua_State* L, const char* Name, const luaL_Reg regfunc[], int i);

/**
 * @brief Dumps the contents of the Lua stack for debugging purposes.
 *
 * This function dumps the contents of the Lua stack for debugging purposes.
 *
 * @param L Pointer to the Lua state.
 * @return int Number of elements on the stack.
 */
int DumpLuaStack(lua_State* L);


/**
 * @brief Pushes a set of functions onto a table in the Lua environment.
 *
 * This function pushes a set of functions specified by the luaL_Reg array onto a table with the given name in the Lua environment.
 *
 * @param L Pointer to the Lua state.
 * @param TableName Name of the table where the functions will be pushed.
 * @param regfunc Array of luaL_Reg structures containing function information.
 */
void PushFuncToTable(lua_State* L, char* TableName, const luaL_Reg regfunc[]);

/**
 * @brief Pushes a set of functions onto the Lua stack.
 *
 * This function pushes a set of functions specified by the luaL_Reg array onto the Lua stack.
 *
 * @param L Pointer to the Lua state.
 * @param regfunc Array of luaL_Reg structures containing function information.
 */
void PushFunc(lua_State* L, const luaL_Reg regfunc[]);

inline void lua_remove(lua_State* L, int idx);



inline void lua_registerfunction(lua_State* L, int registry, const char* path, lua_CppFunction func, const char* text);
void lua_pushcppfunction(lua_State* L, lua_CppFunction func, const char* txt);
inline void lua_register(lua_State* L, const char* path, lua_CppFunction func);
void lua_pushobject(lua_State* L, uint64_t guid, const char* Field);
uint64_t lua_checkobject(lua_State* L, int pos, const char* Field);