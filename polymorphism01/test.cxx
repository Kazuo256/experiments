
#include <cstdio>

class A {
  public:
    virtual void method() = 0;
};

class B : public A {
  public:
    void method() { puts("hey!"); }
};

typedef void (A::*m_type) ();

int main () {

    A* obj = new B;
    m_type mtd = &A::method;

    (obj->*mtd)();

    delete obj;

    return 0;
}

