cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

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
  ${CURSES_LIBRARIES}
  )

target_include_directories(
  terminal_frontend
  PUBLIC
  ${chip8_emu_SOURCE_DIR}/lib/chip8
  ${CURSES_INCLUDE_DIR}
)
