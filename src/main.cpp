#include <iostream>

#include "chip8.hpp"
#include "file_rom.hpp"

#include "terminal_frontend.hpp"

int main() {
  chip8::Chip8Interface interface(term_chip8::updateDisplay,
                                  [](chip8::Chip8 *) {});
  chip8::Chip8 chip8 = chip8::Chip8(interface);

  // auto res = chip8.loadRom("files/roms/bc_test.ch8");
  auto res = chip8.loadRom(
      std::make_unique<chip8::FileROM>("files/roms/IBM Logo.ch8"));
  if (res) {
    chip8.run();
  } else {
    std::cout << "couldn't load the rom ):\n";
  }
}
