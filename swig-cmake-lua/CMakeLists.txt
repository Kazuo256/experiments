
cmake_minimum_required (VERSION 2.8)

project (test CXX)

set (SRC_DIR src/)
set (LIB_DIR lib/)

set (BASE_SRC
  ${SRC_DIR}/vec.cxx
  ${SRC_DIR}/vec.h
  #build/vec_wrap.cxx
)

set (INTERFACE_SRC
  ${SRC_DIR}/vec.i
)

find_package (Lua51 REQUIRED)

include_directories (${SRC_DIR} ${LUA_INCLUDE_DIR})

#add_library (base SHARED ${BASE_SRC})

find_package (SWIG REQUIRED)
include (${SWIG_USE_FILE})

set (CMAKE_SWIG_FLAGS "")
set (CMAKE_SWIG_OUTDIR "swig")

set_source_files_properties (${INTERFACE_SRC} PROPERTIES CPLUSPLUS ON)
set_source_files_properties (${INTERFACE_SRC} PROPERTIES SWIG_FLAGS "-includeall")

swig_add_module (base lua ${INTERFACE_SRC} ${BASE_SRC})
swig_link_libraries (base ${LUA_LIBRARIES})


