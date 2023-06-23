#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "basics.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static const int WIDTH = 10;
static const int HEIGHT = 10;

FILE *global_output;

static FILE *start_gnuplot() {
  FILE *output;
  int pipes[2];
  pid_t pid;
  if (pipe(pipes)) {
    return NULL;
  }
  pid = fork();
  if (!pid) {
    // we are in child
    dup2(pipes[0], STDIN_FILENO);
    char *const args[] = {"gnuplot", NULL};
    execvp("gnuplot", args);
    /*unreachable*/
    return NULL;
  }
  output = fdopen(pipes[1], "w");

  fprintf(output, "set multiplot\n");
  fprintf(output, "set parametric\n");
  fprintf(output, "set xrange [-%d:%d]\n", WIDTH, WIDTH);
  fprintf(output, "set yrange [-%d:%d]\n", HEIGHT, HEIGHT);
  fprintf(output, "set size ratio -1\n");
  fprintf(output, "unset xtics\n");
  fprintf(output, "unset ytics\n");
  fflush(output);
  return output;
}

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

int main(int argc, char **argv, char **envp) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  char *err_desc;
  size_t err_len;
  global_output = start_gnuplot();
  register_functions(L);
  tortoise_reset();
  if (luaL_loadfile(L, NULL) == LUA_OK) {
    if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
		// nothing to do just yet
    } else {
      err_desc = (char *)lua_tolstring(L, lua_gettop(L), &err_len);
      fprintf(stderr, "Error occured!\n\"%s\"\n", err_desc);
    }
  } else {
    err_desc = (char *)lua_tolstring(L, lua_gettop(L), &err_len);
    fprintf(stderr, "Error occured!\n\"%s\"\n", err_desc);
  }
  lua_close(L);
  return EXIT_SUCCESS;
}
