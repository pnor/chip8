cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  terminal_frontend
  SHARED
  terminal_frontend.cpp
  terminal_input.cpp
)

target_link_libraries(
  terminal_frontend
  PRIVATE
  chip8
  )

target_include_directories(
  terminal_frontend
  PUBLIC
  ${emacs_chip8_SOURCE_DIR}/lib/chip8
)
