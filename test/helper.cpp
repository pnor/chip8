#include "helper.hpp"

Chip8 initChip8(std::optional<std::unique_ptr<chip8::IROM>> rom) {
  chip8::Chip8Interface interface(NOP_FUNC, NOP_FUNC);
  Chip8 chip8(interface);
  if (rom.has_value()) {
    chip8.loadRom(std::move(rom.value()));
  }
  chip8.config.setRandomSeed(0);
  return chip8;
}
