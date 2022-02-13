cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
  emacs_chip8_test
  chip8_tests.cpp
  helper.cpp
  helper.hpp
  instructions/add.cpp
  instructions/add_registers.cpp
  instructions/binary_and.cpp
  instructions/binary_or.cpp
  instructions/binary_xor.cpp
  instructions/clear_screen.cpp
  instructions/display.cpp
  instructions/jump.cpp
  instructions/set.cpp
  instructions/set_index_register.cpp
  instructions/set_register_x_to_y.cpp
  instructions/skip.cpp
  instructions/subroutine.cpp
  instructions/subtract.cpp
  instructions/shift.cpp
)

target_link_libraries(
  emacs_chip8_test
  PRIVATE
  gtest_main
  chip8
  emacs_frontend
)

target_include_directories(
  emacs_chip8_test
  PUBLIC
  ${emacs_chip8_SOURCE_DIR}
  ${emacs_chip8_SOURCE_DIR}/lib/chip8
  ${emacs_chip8_SOURCE_DIR}/lib/emacs_frontend
  ${emacs_chip8_SOURCE_DIR}/lib/term_frontend
)
