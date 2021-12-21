cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS ${CMAKE_CXX_COMPILER})

if (APPLE)
# TODO hacky lol
  set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")
endif()

add_executable(
  hw4
  main.cpp
)

add_library(
  hw4-lib
  SHARED
  cmdline_args.cpp
  cmdline_args.hpp
  helper.hpp
  mapreduce.cpp
  mapreduce.hpp
  n_gram.cpp
  n_gram.hpp
)
set_target_properties(hw4-lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(
  hw4
  PRIVATE
  hw4-lib
  boolinq
  wc++
  pthread
)
target_include_directories(
  hw4
  PUBLIC
  ${hw4_SOURCE_DIR}
  ${hw4_SOURCE_DIR}/lib/boolinq
  ${hw4_SOURCE_DIR}/lib/wc++
)

target_include_directories(
  hw4-lib
  PUBLIC
  ${hw4_SOURCE_DIR}
  ${hw4_SOURCE_DIR}/lib/boolinq
  ${hw4_SOURCE_DIR}/lib/wc++
)
