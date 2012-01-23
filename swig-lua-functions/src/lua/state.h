
#ifndef PROG_LUA_STATE_H_
#define PROG_LUA_STATE_H_

#include <cstdlib>
#include <cstdio>

#include <string>

//#include <boost/tr1/memory.hpp>
#include <memory>

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#ifndef LUA_OK
# define LUA_OK (0)
#endif

}


namespace lua {

class status {
  public:
    // Restriction: a callable object must return int when called.
    template <typename Callable>
    explicit status (Callable c) :
      s_(c()) {}

#define DECLARE_LUA_CONSTANT(name) \
  static const status name () { return status(LUA_##name); }
    
    DECLARE_LUA_CONSTANT(OK)
    DECLARE_LUA_CONSTANT(ERRRUN)
    DECLARE_LUA_CONSTANT(ERRMEM)
    DECLARE_LUA_CONSTANT(ERRERR)
    DECLARE_LUA_CONSTANT(ERRSYNTAX)
    DECLARE_LUA_CONSTANT(ERRFILE)

#undef DECLARE_LUA_CONSTANT

    bool operator == (const status& st) const { return s_ == st.s_; }
    bool operator != (const status& st) const { return s_ != st.s_; }
  private:
    status (int s) : s_(s) {}
    int s_;
};


class State {

  public:

    State () :
      L(luaL_newstate(), lua_close) {
        if (L.get() == NULL)
          State::errormsg("Could not create Lua state.");
    }

    void init ();

    void pushvalue (int index) { lua_pushvalue(L.get(), index); }
    void pushnil () { lua_pushnil(L.get()); }

    void push (bool b) { lua_pushboolean(L.get(), b); }
    void push (lua_Integer integer) { lua_pushinteger(L.get(), integer); }
    void push (lua_Number number) { lua_pushnumber(L.get(), number); }
    void push (void *ptr) { lua_pushlightuserdata(L.get(), ptr); }
    void push (const char* str) { lua_pushstring(L.get(), str); }
    void push (lua_CFunction func, int n = 0) { lua_pushcclosure(L.get(), func, n); }
    
    void call (int nargs, int nresults) { lua_call(L.get(), nargs, nresults); }

    const status tracedcall (int nargs, int nresults) {
      return report(dotracedcall(nargs, nresults));
    }
    
    const status dofile (const char* filename);

  private:

    // TODO: make-do for now.
    static void errormsg (std::string msg) {
      fprintf(stderr, "lua: %s\n", msg.c_str());
    }

    const status report (const status& st);
    const status dotracedcall (int nargs, int nres);

    std::tr1::shared_ptr<lua_State> L;

};

}

#endif

