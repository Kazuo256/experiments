
#include <functional>

#include <lua/state.h>

// some C functions from lua.c
extern "C" {

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

} // extern "C"

namespace lua {

using std::tr1::bind;

/// public:

void State::init () {
  // luaL_checkversion(L.get());  // TODO-lua5.2: add this.
  lua_gc(L.get(), LUA_GCSTOP, 0);
  luaL_openlibs(L.get());
  lua_gc(L.get(), LUA_GCRESTART, 0);
}

const status State::dofile (const char* filename) {
  status st = status(bind(luaL_loadfile, L.get(), filename));
  if (st != status::OK()) return st;
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
  return st;
}

#undef check_init

}

