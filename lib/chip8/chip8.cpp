#include "chip8.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "font.hpp"
#include "instruction.hpp"

namespace chip8 {
using std::uint16_t;

//
// ===== Helper =========================
//

#define UNKNOWN_OP_CODE throw std::invalid_argument("unknown op code")

constexpr std::uint8_t lastNibble(OpCodeArgs args) { return args & 0x000F; }

//
// ===== Setting Up =========================
//

void Chip8::setupFonts() {
  auto *memPtr = &memory[0x50];
  for (size_t i = 0; i < NUM_FONTS; i++) {
    writeFontToMemory(memPtr, FONTS[i]);
    memPtr += FONT_BYTE_LENGTH;
  }
}

Chip8::Chip8(Chip8Interface interface) : interface(interface) {
  std::fill(this->memory.begin(), this->memory.end(), std::byte(0));

  for (size_t i = 0; i < display.size(); i++) {
    std::fill(display[i].begin(), display[i].end(), false);
  }

  setupFonts();
}

//
// ===== Running Chip8 System =========================
//

void Chip8::loadRom() {
  // TODO
  // "expect a CHIP-8 programto be loaded into memory at address 0x200 (512 in
  // decimal)"
}

Instruction Chip8::fetch() {
  uint16_t instruction = static_cast<uint16_t>(memory[PC]);
  instruction <<= 8;
  instruction += static_cast<uint16_t>(memory[PC + 1]);
  PC += 2;
  return instruction;
}

void Chip8::decodeAndExecute(Instruction instruction) {
  OpCode opCode = (instruction & 0xF000) >> 12;
  OpCodeArgs args = instruction & 0x0FFF;
  switch (opCode) {
  case 0x0: {
    auto nibble = lastNibble(args);
    if (nibble == 0x0) {
      Instructions::clearScreen(this, args);
    } else if (nibble == 0xE) {
      Instructions::popSubroutine(this, args);
    } else {
      UNKNOWN_OP_CODE;
    }
    break;
  }
  case 0x1: {
    Instructions::jump(this, args);
    break;
  }
  case 0x2: {
    Instructions::pushSubroutine(this, args);
    break;
  }
  case 0x6: {
    Instructions::setRegister(this, args);
    break;
  }
  case 0x7: {
    Instructions::addValueToRegister(this, args);
    break;
  }
  case 0xA: {
    Instructions::setIndexRegisterI(this, args);
    break;
  }
  case 0xD: {
    Instructions::display(this, args);
    break;
  }
  default: {
    UNKNOWN_OP_CODE;
  }
  }
}

void Chip8::run() {
  // TODO
  // fetch decode exec

  // TODO only do loop based on instructionsPerSecond
  Instruction instruction = fetch();
  decodeAndExecute(instruction);
}

//
// ===== State of the System =========================
//

std::array<std::byte, 4 * KILOBYTE> Chip8::dumpMemory() { return memory; }

const std::array<std::array<bool, Chip8::DISPLAY_HEIGHT>, Chip8::DISPLAY_WIDTH>
    &Chip8::getDisplay() {
  return display;
}

} // namespace chip8
