
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
extern int luaopen_proto (lua_State *);
}

#include <cstdio>

#include <string>

#include <core/vec.h>
#include <lua/state.h>


int main () {
  lua::State L;
  L.init();
  L.push(luaopen_proto);
  L.push("core");
  if (L.tracedcall(1, LUA_MULTRET) != lua::status::OK()) {
    puts("NOT");
    return EXIT_FAILURE;
  }
  if (L.dofile("scripts/prog.lua") != lua::status::OK()) {
    puts("FAIL");
    return EXIT_FAILURE;
  }
  /*
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
  */
  return 0;
}


