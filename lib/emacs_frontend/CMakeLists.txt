cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  emacs_frontend
  SHARED
  emacs_frontend.cpp
  emacs_frontend.hpp
  emacs-module.h
)

target_link_libraries(
  emacs_frontend
  PRIVATE
  chip8
  )
