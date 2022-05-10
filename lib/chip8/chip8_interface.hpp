#ifndef CHIP8_INTERFACE_H_
#define CHIP8_INTERFACE_H_

#include <functional>
#include <memory>

#include "chip8_input.hpp"

namespace chip8 {

class Chip8;

/** Bridge between `Chip8` and the frontends */
class Chip8Interface {
private:
  std::function<void(Chip8 *chip8)> updateDisplayHook;
  std::function<void(Chip8 *chip8)> soundHook;

public:
  Chip8Interface(std::unique_ptr<IInput> input,
                 std::function<void(chip8::Chip8 *)> updateDisplayHook,
                 std::function<void(chip8::Chip8 *)> soundHook);

  std::unique_ptr<IInput> input;

  void callDisplayHook(Chip8 *chip8);
  void callSoundHook(Chip8 *chip8);
};

} // namespace chip8

#endif // CHIP8_INTERFACE_H_
