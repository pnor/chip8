#include <iostream>

#include "chip8.hpp"

#include "terminal_frontend.hpp"

int main() {
  chip8::Chip8Interface interface(term_chip8::updateDisplay,
                                  [](chip8::Chip8 *) {});
  chip8::Chip8 chip8 = chip8::Chip8(interface);
  std::cout << "hello world (:" << std::endl;
}
