#ifndef CHIP8_INPUT_H_
#define CHIP8_INPUT_H_

#include "key_code.hpp"

/** Abstraction for input events to Chip8 */
class IInput {
public:
  /** Check the state of a key without blocking */
  virtual bool pollKeyState(const KeyCode code) = 0;
  /** Check if a key is pressed */
  virtual std::optional<KeyCode> keyPressed() = 0;

  virtual ~IInput() = default;
};
#endif // CHIP8_INPUT_H_
