#include "file_rom.hpp"
#include <iostream>

namespace chip8 {

FileROM::FileROM(std::filesystem::path path) {
  file = std::ifstream(path, std::ios::binary);
}

Instruction FileROM::next() {
  Instruction instruction;

  std::array<char, 2> twoRomBytes;
  std::fill(twoRomBytes.begin(), twoRomBytes.end(), 0);
  file.read(twoRomBytes.begin(), 2);
  instruction = twoRomBytes[0] << 8;
  instruction += 0x00FF & twoRomBytes[1];

  return instruction;
}

bool FileROM::done() const { return file.eof(); }

} // namespace chip8
