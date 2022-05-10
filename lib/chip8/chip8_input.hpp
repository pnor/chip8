#ifndef CHIP8_INPUT_H_
#define CHIP8_INPUT_H_

/** Abstraction for input events to Chip8 */
class IInput {
public:
  /** Check the state of a key without blocking */
  virtual bool pollKeyState(/* TODO */) = 0;
  /** Block until next keypress is pushed down */
  virtual bool waitForKeyPressed(/* TODO */) = 0;
  /** Block until next keypress is pushed down then released */
  virtual bool waitForKeyPress(/* TODO */) = 0;

  virtual ~IInput() = default;
};
#endif // CHIP8_INPUT_H_
