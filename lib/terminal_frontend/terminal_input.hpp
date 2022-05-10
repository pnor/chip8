#ifndef TERMINAL_INPUT_H_
#define TERMINAL_INPUT_H_

#include "chip8_input.hpp"

// Input Source for Chip8 that prints to a terminal
class TerminalInput : public IInput {
public:
  virtual bool pollKeyState();
  virtual bool waitForKeyPressed();
  virtual bool waitForKeyPress();
};

#endif // TERMINAL_INPUT_H_
