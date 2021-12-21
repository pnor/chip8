cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE)
# TODO hacky lol
  set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")
endif()

# Controller
add_library(
  boolinq
  SHARED
  boolinq.h
)

set_target_properties(boolinq PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET boolinq PROPERTY CXX_STANDARD 17)
