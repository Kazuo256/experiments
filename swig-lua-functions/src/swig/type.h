
#ifndef PROG_SWIG_TYPE_H_
#define PROG_SWIG_TYPE_H_

#ifndef SWIG
#include <cstdlib>
#include <cstdio>
#include <swig/swigluarun.h>
#endif

namespace swig {

class type {
  public:
    void set (swig_type_info* info) {
      if (!info_) info_ = info;
    }
    swig_type_info* get () const {
      return info_;
    }
  protected:
    type () : info_(NULL) {}
  private:
    swig_type_info* info_;
};

template <typename T>
class singleton_type : public type {
  public:
    static singleton_type<T>& ref () { return ref_; }
  private:
    singleton_type () {}
    static singleton_type<T> ref_;
};

template <typename T>
singleton_type<T> singleton_type<T>::ref_;

template <typename T>
void register_type (T* tp) {
  puts("HUZZAH");
}

}

#endif

