#include "chip8.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "font.hpp"
#include "instruction.hpp"
#include "irom.hpp"

namespace chip8 {
using std::uint16_t;

//
// ===== Helper =========================
//

#define UNKNOWN_OP_CODE throw std::invalid_argument("unknown op code")

constexpr std::uint8_t lastNibble(OpCodeArgs args) { return args & 0x000F; }
constexpr size_t ROM_START_ADDRESS = 0x200;

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

  PC = ROM_START_ADDRESS;
  I = 0;
  delayTimer = 0;
  soundTimer = 0;

  std::fill(registers.begin(), registers.end(), 0);

  setupFonts();
}

//
// ===== Running Chip8 System =========================
//

bool Chip8::loadRom(std::unique_ptr<IROM> rom) {
  std::byte *memPtr = memory.begin() + ROM_START_ADDRESS;

  while (!rom->done()) {
    Instruction instruction = rom->next();
    *memPtr = static_cast<std::byte>(instruction >> 8);
    memPtr++;
    *memPtr = static_cast<std::byte>(instruction & 0x00FF);
    memPtr++;
  }

  return memPtr < memory.end();
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

  // make sure args never has bits sent in first 4 bits
  assert((args & 0xF000) >> 12 == 0);

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
  case 0x3: {
    Instructions::skipIfEqualImmediate(this, args);
    break;
  }
  case 0x4: {
    Instructions::skipIfNotEqualImmediate(this, args);
    break;
  }
  case 0x5: {
    Instructions::skipIfRegistersEqual(this, args);
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
  case 0x9: {
    Instructions::skipIfRegistersNotEqual(this, args);
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

void Chip8::cycle() {
  Instruction instruction = fetch();
  decodeAndExecute(instruction);
}

void Chip8::run() {
  while (true) {
    cycle();
  }
}

//
// ===== State of the System =========================
//

std::array<std::byte, 4 * KILOBYTE> Chip8::getMemory() const { return memory; }

const std::array<std::array<bool, Chip8::DISPLAY_WIDTH>, Chip8::DISPLAY_HEIGHT>
    &Chip8::getDisplay() const {
  return display;
}

std::size_t Chip8::getPC() const { return PC; }

std::uint16_t Chip8::getI() const { return I; }

const std::vector<std::uint16_t> &Chip8::getStack() const { return stack; }

std::uint8_t Chip8::valueInRegister(size_t reg) const {
  return registers.at(reg);
}

} // namespace chip8
