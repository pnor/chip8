#include <format>
#include <iostream>
#include <ncurses.h>

#include "terminal_frontend.hpp"

namespace term_chip8 {

// TODO test input

void setupDisplay() {
  initscr();
  keypad(stdscr, true);
  cbreak();
  noecho();
  timeout(1000);

  // ...
  // initscr();
  // keypad(stdscr, true);
  // // cbreak();
  // // noecho();
  // // timeout(1000);
  // printw("Hello World !!!");
  // refresh();

  // for (int i = 0; i < 5; i++) {
  //   int key = getch();
  //   printw("%s", std::format("pressed key code {}", key).c_str());
  //   refresh();
  // }

  // mvaddch(2, 1, ' '); // add and advance
  // addch('$');
  // mvaddch(4, 2, '$');
  // refresh();

  // // add a single character

  // getch();
  // endwin();
}

void teardownDisplay() { endwin(); }

void updateDisplay(chip8::Chip8 *chip8) {
  // clear screen kinda
  move(0, 0);
  clrtoeol();
  // for (size_t i = 0; i < 3; i++) {
  //   std::cout << "\n";
  // }

  const auto &display = chip8->getDisplay();
  for (size_t i = 0; i < display.size(); i++) {
    for (size_t j = 0; j < display[i].size(); j++) {
      // std::cout << (display[i][j] ? "█" : "░");
      mvaddch(i, j, (display[i][j] ? '#' : ' '));
    }
    // std::cout << "\n";
  }

  // std::cout << std::flush;
  refresh();
}

} // namespace term_chip8
