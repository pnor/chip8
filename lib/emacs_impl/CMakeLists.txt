cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  emacs_impl
  SHARED
  emacs_impl.cpp
  emacs_impl.hpp
  emacs-module.h
)

target_link_libraries(
  emacs_impl
  PRIVATE
  chip8
  )
