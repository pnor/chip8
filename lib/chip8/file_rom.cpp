#include "file_rom.hpp"

namespace chip8 {

FileROM::FileROM(std::filesystem::path path) {
  file = std::ifstream(path, std::ios::binary);
}

Instruction FileROM::next() {
  Instruction instruction;

  char romByte;

  file.read(&romByte, 1);
  if (!file.good()) {
    throw std::runtime_error(
        "failed to fetch first byte of an instruction from ROM!");
  }
  instruction = static_cast<uint8_t>(romByte) << 8;

  file.read(&romByte, 1);
  if (!file.good()) {
    throw std::runtime_error(
        "failed to fetch second byte of an instruction from ROM!");
  }
  instruction += static_cast<uint8_t>(romByte);

  return instruction;
}

bool FileROM::done() const { return file.good(); }

} // namespace chip8
