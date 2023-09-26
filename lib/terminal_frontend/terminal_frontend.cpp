#include <format>
#include <ncurses.h>

#include "terminal_frontend.hpp"

namespace term_chip8 {

void setupDisplay() {
  initscr();
  keypad(stdscr, true);
  cbreak();
  noecho();
  timeout(1000);
}

void teardownDisplay() { endwin(); }

void updateDisplay(chip8::Chip8 *chip8) {
  move(0, 0);
  clrtoeol();

  const auto &display = chip8->getDisplay();
  for (size_t i = 0; i < display.size(); i++) {
    for (size_t j = 0; j < display[i].size(); j++) {
      mvaddch(i, j, (display[i][j] ? '#' : ' '));
    }
  }

  refresh();
}

} // namespace term_chip8
