
#ifndef PROG_FUNCTION_CALLER_H_
#define PROG_FUNCTION_CALLER_H_

/////////////////
#include <string>
#include <memory>
#include <utility>
/////////////////
//#include <lua/state.h>
#include <function/handler.h>
/////////////////
#include <swig/type.h>

namespace function {

class caller {

  public:

    //caller (std::tr1::shared_ptr<handler> h) :
    //  h_(h) {}
    caller () {}

    template <typename T>
    T call () { /* bad */ }

    template <typename R, typename A>
    R* call (A *a) {
      handler h;
      h.add_arg(a);
      h.call();
      return static_cast <R*> (h.ret());
    }

    template <typename R, typename A1, typename A2>
    R* call (A1 *a1, A2 *a2) {
      handler h;
      h.add_arg(a1);
      h.add_arg(a2);
      h.call();
      return static_cast <R*> (h.ret());
    }

    template <typename R1, typename R2, typename A>
    std::pair<R1*,R2*> call (A *a) {
      handler h;
      h.add_arg(a);
      h.call();
      return
        std::pair <R1*, R2*> (
          static_cast <R1*> (h.ret()),
          static_cast <R2*> (h.ret())
        );
    }

  private:

    //lua::state L_;
    //std::tr1::shared_ptr<handler> h_;

};

}

#endif


