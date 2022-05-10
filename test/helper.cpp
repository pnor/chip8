#include "helper.hpp"

bool TestInput::pollKeyState() { return true; }

bool TestInput::waitForKeyPressed() { return true; }

bool TestInput::waitForKeyPress() { return true; }

Chip8 initChip8(std::optional<std::unique_ptr<chip8::IROM>> rom) {
  chip8::Chip8Interface interface(std::make_unique<TestInput>(), NOP_FUNC,
                                  NOP_FUNC);
  Chip8 chip8(std::move(interface));
  if (rom.has_value()) {
    chip8.loadRom(std::move(rom.value()));
  }
  chip8.config.setRandomSeed(0);
  return chip8;
}
