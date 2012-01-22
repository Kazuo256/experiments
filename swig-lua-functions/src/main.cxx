
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
extern int luaopen_proto (lua_State *);
}

#include <core/vec.h>
#include <lua/func.h>


static int report (lua_State *L, int status) {
  if (status && !lua_isnil(L, -1)) {
    const char *msg = lua_tostring(L, -1);
    if (msg == NULL) msg = "(error object is not a string)";
    l_message(progname, msg);
    lua_pop(L, 1);
  }
  return status;
}

static int traceback (lua_State *L) {
  lua_getfield(L, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}

int main () {
  int status;
  lua_State *L;
  L=luaL_newstate();
  luaL_openlibs(L); // load basic libs (eg. print)
  luaopen_proto(L); // load the wrappered module
  lua_pushcfunction(L, traceback);
  if (luaL_loadfile(L,"src/prog.lua")==0) { // load and run the file
    status = lua_pcall(L,0,0,-1);
    puts("Lua called!");
  }
  else
    printf("unable to load %s\n","prog.lua");
  //lua_pop(L,1);
  if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
  report(L,status);
  lua_close(L);
  return 0;
}


