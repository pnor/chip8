#include <iostream>

#include "chip8.hpp"
#include "file_rom.hpp"

#include "terminal_frontend.hpp"
#include "terminal_input.hpp"

int main() {
  std::unique_ptr<IInput> input = std::make_unique<TerminalInput>();
  chip8::Chip8Interface interface(std::move(input), term_chip8::updateDisplay,
                                  [](chip8::Chip8 *) {});
  chip8::Chip8 chip8 = chip8::Chip8(std::move(interface));
  chip8.init();

  auto res =
      chip8.loadRom(std::make_unique<chip8::FileROM>("files/roms/bc_test.ch8"));
  // auto res = chip8.loadRom(
  //     std::make_unique<chip8::FileROM>("files/roms/IBM Logo.ch8"));
  if (res) {
    chip8.run();
  } else {
    std::cout << "couldn't load the rom ):\n";
  }
}
