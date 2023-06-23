#include "luad.h"
#include "basics.h"

int lua_tortoise_reset(lua_State *L) {
  tortoise_reset();
  lua_pushinteger(L, 0);
  return 1;
}

int lua_tortoise_penup(lua_State *L) {
  int r = tortoise_penup();
  lua_pushinteger(L, r);
  return 1;
}

int lua_tortoise_pendown(lua_State *L) {
  int r = tortoise_pendown();
  lua_pushinteger(L, r);
  return 1;
}

int lua_tortoise_turn(lua_State *L) {
  double angle = luaL_checknumber(L, 1);
  double new_angle = tortoise_turn(angle);
  lua_pushnumber(L, new_angle);
  return 1;
}

int lua_tortoise_move(lua_State *L) {
  double step = luaL_checknumber(L, 1);
  struct coord_pair r = tortoise_move(step);
  lua_pushnumber(L, r.x);
  lua_pushnumber(L, r.y);
  return 2;
}

void register_functions(lua_State *L) {
  lua_register(L, "tortoise_reset", lua_tortoise_reset);
  lua_register(L, "tortoise_penup", lua_tortoise_penup);
  lua_register(L, "tortoise_pendown", lua_tortoise_pendown);
  lua_register(L, "tortoise_turn", lua_tortoise_turn);
  lua_register(L, "tortoise_move", lua_tortoise_move);
}
