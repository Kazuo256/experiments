
%module proto
%{
#include <cstdio>
#include <string>

#include "core/vec.h"
#include "lua/func.h"
#define SWIG
#include "swig/type.h"
#undef SWIG
%}

%define register_class(T)
%typemap(in) T* tp {
  // SUPIMPA MANO
  swig::singleton_type<$*1_type>::ref().set($1_descriptor);
  $1 = NULL;
}
%template(register_type_##T) swig::register_type<T>;
%typemap(in) T* tp;
%template(get_null_##T) swig::get_null<T>;
%enddef


%include "swig/type.h"
%include "core/vec.h"
%include "lua/func.h"

%wrapper %{
// HUZZAH
%}

%luacode {
for k,v in pairs(proto) do
  m = string.match(k, "register_type_(.+)")
  if m then
    proto[k](proto["get_null_"..m]())
  end
end
}

