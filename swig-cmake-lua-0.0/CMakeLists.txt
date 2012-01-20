
cmake_minimum_required (VERSION 2.8)

project (test CXX)

set (SRC_DIR src/)
set (LIB_DIR lib/)

set (BASE_SRC
  ${SRC_DIR}/vec.cxx
  ${SRC_DIR}/vec.h
  build/vec_wrap.cxx
)

set (INTERFACE_SRC
  ${SRC_DIR}/vec.i
)

find_package(Lua51 REQUIRED)

include_directories (${SRC_DIR} ${LUA_INCLUDE_DIR})

add_library (base SHARED ${BASE_SRC})


