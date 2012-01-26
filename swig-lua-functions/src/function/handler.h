
#ifndef PROG_FUNCTION_HANDLER_H_
#define PROG_FUNCTION_HANDLER_H_

namespace function {

class handler {

  public:

    handler () {}
    ~handler () {}

    virtual void add_arg (void* data) {}
    virtual void call () {}
    virtual void* ret () { return NULL; }

};

}

#endif

