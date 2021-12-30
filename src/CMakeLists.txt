cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  emacs_chip8
  main.cpp
)

target_link_libraries(
  emacs_chip8
  PRIVATE
  chip8
  emacs_frontend
  terminal_frontend
)

target_include_directories(
  emacs_chip8
  PUBLIC
  ${emacs_chip8_SOURCE_DIR}
  ${emacs_chip8_SOURCE_DIR}/lib/emacs_frontned
  ${emacs_chip8_SOURCE_DIR}/lib/terminal_frontend
  ${emacs_chip8_SOURCE_DIR}/lib/chip8
)
