
#ifndef BASE_FUNC_H_
#define BASE_FUNC_H_

/*
extern "C" {
#include <swigluarun.h>
}
*/

#ifndef SWIG
# include <cstdio>
# include <string>
//# include <swigluarun.h>
#endif

namespace base {

class func {
  public:

    void* operator () () {}
};

//template <typename T>
//class func {};

class lua_func : public func {
  public:
    lua_func (lua_State *L, lua_CFunction cf) {}
    lua_func (lua_State *L, int index) {}
};

inline void register_func (func *f) {
  std::string text = "Function registered!";
  puts(text.c_str());
}


}

#endif

