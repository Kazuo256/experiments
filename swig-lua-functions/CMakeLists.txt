
cmake_minimum_required (VERSION 2.8)

project (test CXX)

set (SRC_DIR src/)
set (INCLUDE_DIRS ${SRC_DIR})

set (SRC
  ${SRC_DIR}/main.cxx
  ${SRC_DIR}/core/vec.cxx
  ${SRC_DIR}/core/vec.h
  ${SRC_DIR}/lua/func.h
  ${SRC_DIR}/lua/state.cxx
  ${SRC_DIR}/lua/state.h
)

set (INTERFACE_SRC
  ${SRC_DIR}/core/core.i
)

find_package (Lua51 REQUIRED)
if (NOT LUA51_FOUND)
  message("HEY")
else ()
  message("LUA: ${LUA_LIBRARIES}")
endif ()

find_package (Boost 1.48.0 REQUIRED)
if (Boost_FOUND)
  message ("Boost rootdir: ${Boost_INCLUDE_DIRS}")
  set (INCLUDE_DIRS ${INCLUDE_DIRS} "${Boost_INCLUDE_DIRS}/boost/tr1/tr1" ${Boost_INCLUDE_DIRS})
else (Boost_FOUND)
  message (FATAL_ERROR "Boost not found.")
endif ()

include_directories (${INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

find_package (SWIG REQUIRED)
#include (${SWIG_USE_FILE})
include (cmake/UseSWIG.cmake)

set (CMAKE_SWIG_FLAGS "")
set (CMAKE_SWIG_OUTDIR "swig")

set_source_files_properties (${INTERFACE_SRC} PROPERTIES CPLUSPLUS ON)
set_source_files_properties (${INTERFACE_SRC} PROPERTIES SWIG_FLAGS "-includeall")

swig_add_module (base lua ${INTERFACE_SRC} ${SRC})
#swig_link_libraries (base ${LUA_LIBRARIES})

add_executable (prog ${SRC} ${swig_generated_sources})
target_link_libraries (prog ${LUA_LIBRARIES})
set_target_properties (prog PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)


