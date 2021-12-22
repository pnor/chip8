cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  emacs_chip8_test
  test.cpp
)

target_link_libraries(
  emacs_chip8_test
  PRIVATE
  chip8
  emacs_impl
)


target_include_directories(
  emacs_chip8_test
  PUBLIC
  ${emacs_chip8_SOURCE_DIR}
  ${emacs_chip8_SOURCE_DIR}/lib/chip8
  ${emacs_chip8_SOURCE_DIR}/lib/emacs_impl
)
