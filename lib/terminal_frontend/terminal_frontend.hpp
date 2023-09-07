#ifndef TERMINAL_FRONTEND_H_
#define TERMINAL_FRONTEND_H_

#include "chip8.hpp"

namespace term_chip8 {

void setupDisplay();

void teardownDisplay();

void updateDisplay(chip8::Chip8 *chip8);

} // namespace term_chip8

#endif // TERMINAL_FRONTEND_H_
