#ifndef __TORTOISE_TUTORIAL_LUA_H_GUARD__
#define __TORTOISE_TUTORIAL_LUA_H_GUARD__
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int lua_tortoise_reset(lua_State *L);
int lua_tortoise_penup(lua_State *L);
int lua_tortoise_pendown(lua_State *L);
int lua_tortoise_turn(lua_State *L);
int lua_tortoise_move(lua_State *L);
void register_functions(lua_State *L);
#endif //__TORTOISE_TUTORIAL_LUA_H_GUARD__
