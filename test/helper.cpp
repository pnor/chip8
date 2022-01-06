#include "helper.hpp"

Chip8 initChip8(std::unique_ptr<chip8::IROM> rom) {
  chip8::Chip8Interface interface(NOP_FUNC, NOP_FUNC);
  Chip8 chip8(interface);
  chip8.loadRom(std::move(rom));
  return chip8;
}
