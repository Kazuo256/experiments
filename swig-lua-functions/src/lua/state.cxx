
#include <functional>

#include <lua/state.h>

extern "C" {

/// some C functions from lua.c

static int traceback (lua_State *L) {
  lua_getglobal(L, "debug");
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

/// some other functions

static const int sentinel_ = 0;
#define sentinel ((void*)&sentinel_)

static int dorequire (lua_State *L) {
  // clean extra args
  lua_settop(L, 2);
  // get first arg
  const char* name = luaL_checkstring(L, 1);
  // get second arg
  luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_CFunction loader = lua_tocfunction(L, 2);
  lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
  // check if the module has already been loaded.
  lua_getfield(L, 3, name);
  if (lua_toboolean(L, -1)) {
    if (lua_touserdata(L, -1) == sentinel)
      return luaL_error(L, "loop or previuous error loading module ", name);
    return 1;
  }
  // nope
  lua_pop(L, 1);
  // so use the loader
  // but first, set up a sentinel to avoid OROBOROS
  lua_pushlightuserdata(L, sentinel);
  lua_setfield(L, 3, name);
  // call loader
  lua_pushcfunction(L, loader);
  lua_pushstring(L, name);
  lua_call(L, 1, 1);
  // check result
  if (!lua_isnil(L, -1))
    lua_setfield(L, 3, name);
  lua_getfield(L, 3, name);
  // if no result, put true
  if (lua_touserdata(L, -1) == sentinel) {
    lua_pushboolean(L, true);
    lua_pushvalue(L, -1); // repeat
    lua_setfield(L, 3, name);
  }
  return 1;
}

#undef sentinel

} // extern "C"

namespace lua {

using std::tr1::bind;

/// public:

void State::loadlibs () {
  // luaL_checkversion(L.get());  // TODO-lua5.2: add this.
  lua_gc(L.get(), LUA_GCSTOP, 0);
  luaL_openlibs(L.get());
  lua_gc(L.get(), LUA_GCRESTART, 0);
}

const status State::loadmodule (const char* name, lua_CFunction loader) {
  push(dorequire);
  push(name);
  push(loader);
  return dotracedcall(2,1);
  pop(1);
}

const status State::dofile (const char* filename) {
  status st = status(bind(luaL_loadfile, L.get(), filename));
  if (st != status::OK()) return report(st);
  return dotracedcall(0, LUA_MULTRET);
}

/// private:

const status State::report (const status& st) {
  if (st != status::OK() && !lua_isnil(L.get(), -1)) {
    const char *msg = lua_tostring(L.get(), -1);
    if (msg == NULL) msg = "(error object is not a string)";
    State::errormsg(msg);
    lua_pop(L.get(), 1);
    /* force a complete garbage collection in case of errors */
    lua_gc(L.get(), LUA_GCCOLLECT, 0);
  }
  return st;
}

const status State::dotracedcall (int nargs, int nres) {
  int base = lua_gettop(L.get()) - nargs;
  lua_pushcfunction(L.get(), traceback);
  lua_insert(L.get(), base);
  status st = status(bind(lua_pcall, L.get(), nargs, nres, base));
  //status st = status(L, nargs, nres, base);
  lua_remove(L.get(), base);
  return report(st);
}

}

