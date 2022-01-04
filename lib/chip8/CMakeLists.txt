cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  chip8
  SHARED
  array_rom.hpp
  chip8.cpp
  chip8.hpp
  chip8_interface.cpp
  chip8_interface.hpp
  file_rom.cpp
  file_rom.hpp
  font.hpp
  instruction.cpp
  instruction.hpp
  irom.hpp
)
