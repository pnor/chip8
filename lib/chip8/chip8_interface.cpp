#include "chip8_interface.hpp"

namespace chip8 {

Chip8Interface::Chip8Interface(
    std::function<void(Chip8 *chip8)> updateDisplayHook,
    std::function<void(Chip8 *chip8)> soundHook) {
  this->updateDisplayHook = updateDisplayHook;
  this->soundHook = soundHook;
}

void Chip8Interface::callDisplayHook(Chip8 *chip8) { updateDisplayHook(chip8); }

void Chip8Interface::callSoundHook(Chip8 *chip8) { soundHook(chip8); }

} // namespace chip8
