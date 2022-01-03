#include <iostream>

#include "terminal_frontend.hpp"

namespace term_chip8 {

void updateDisplay(chip8::Chip8 *chip8) {
  // clear screen kinda
  for (size_t i = 0; i < 3; i++) {
    std::cout << "\n";
  }

  const auto &display = chip8->getDisplay();
  for (size_t i = 0; i < display.size(); i++) {
    for (size_t j = 0; j < display[i].size(); j++) {
      std::cout << (display[i][j] ? "█" : "░");
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
}

} // namespace term_chip8
