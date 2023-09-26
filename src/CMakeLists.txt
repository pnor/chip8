cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  chip8_emu
  main.cpp
)

target_link_libraries(
  chip8_emu
  PRIVATE
  chip8
  terminal_frontend
)

target_include_directories(
  chip8_emu
  PUBLIC
  ${chip8_emu_SOURCE_DIR}
  ${chip8_emu_SOURCE_DIR}/lib/terminal_frontend
  ${chip8_emu_SOURCE_DIR}/lib/chip8
)
