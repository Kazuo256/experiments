
%module proto
%{
#include <cstdio>
#include <string>

#define SWIG
#include "core/vec.h"
#include "lua/func.h"
%}


%include "core/vec.h"
%include "lua/func.h"

%wrapper %{
// HUZZAH
%}


%typemap (in) (func* f) %{
  if (lua_isfunction(L, $input)
%}

