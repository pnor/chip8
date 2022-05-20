cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  chip8
  SHARED
  array_rom.hpp
  chip8.cpp
  chip8_config.cpp
  chip8_input.hpp
  chip8_interface.cpp
  file_rom.cpp
  font.hpp
  instruction.cpp
  irom.hpp
  key_code.cpp
)
