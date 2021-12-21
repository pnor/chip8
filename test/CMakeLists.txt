cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE)
# TODO hacky lol
  set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")
endif()

add_executable(
  hw4-test
  test.cpp
  test_lib.cpp
  test_lib.hpp
  ngram_test.cpp
  ngram_test.hpp
)

target_link_libraries(
  hw4-test
  LINK_PRIVATE
  hw4-lib
  boolinq
)

target_link_libraries(
  hw4-test
  LINK_PRIVATE
  hw4-lib
  boolinq
)

target_include_directories(
  hw4-test
  PUBLIC
  ${hw4_SOURCE_DIR}/src
  ${hw4_SOURCE_DIR}/lib/boolinq
  ${hw4_SOURCE_DIR}/lib/wc++
)
