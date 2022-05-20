#include "chip8.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "font.hpp"
#include "instruction.hpp"
#include "irom.hpp"

namespace chip8 {
using std::uint16_t;

//
// ===== Helper =========================
//

static void unknownOpCode(OpCode code, OpCodeArgs args) {
  uint16_t instruction = (code << 12) + args;
  char buf[5];
  std::memset(buf, 0, sizeof(char) * 4);
  std::sprintf(buf, "%X", instruction);
  std::string opCodeString(buf);
  throw std::invalid_argument("unknown op code: " + opCodeString);
}

static constexpr std::uint8_t lastNibble(OpCodeArgs args) {
  return args & 0x000F;
}

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

Chip8::Chip8(Chip8Interface &&interface) : interface(std::move(interface)) {
  std::srand(config.randomSeed());
  reset();
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
  PC += INSTRUCTION_BYTE_SIZE;
  return instruction;
}

void Chip8::decodeAndExecuteArithmetic(OpCodeArgs args) {
  auto nibble = lastNibble(args);

  switch (nibble) {
  case 0x0: {
    Instructions::setRegisterXToY(this, args);
    break;
  }
  case 0x1: {
    Instructions::binaryOR(this, args);
    break;
  }
  case 0x2: {
    Instructions::binaryAND(this, args);
    break;
  }
  case 0x3: {
    Instructions::binaryXOR(this, args);
    break;
  }
  case 0x4: {
    Instructions::addRegisters(this, args);
    break;
  }
  case 0x5: {
    Instructions::subtractYFromX(this, args);
    break;
  }
  case 0x6: {
    Instructions::shiftRightOne(this, args);
    break;
  }
  case 0x7: {
    Instructions::subtractXFromY(this, args);
    break;
  }
  case 0xE: {
    Instructions::shiftLefttOne(this, args);
    break;
  }
  default: {
    unknownOpCode(8, args);
  }
  }
}

void Chip8::decodeAndExecuteInputSkips(OpCodeArgs args) {
  const uint8_t lastByte = args & 0x00FF;
  switch (lastByte) {
  case 0x9E: {
    Instructions::skipIfKeyPressed(this, args);
    break;
  }
  case 0xA1: {
    Instructions::skipIfKeyNotPressed(this, args);
    break;
  }
  default: {
    unknownOpCode(0xE, args);
  }
  }
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
      unknownOpCode(opCode, args);
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
  case 0x8: {
    decodeAndExecuteArithmetic(args);
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
  case 0xB: {
    Instructions::jumpWithOffset(this, args);
    break;
  }
  case 0xC: {
    Instructions::random(this, args);
    break;
  }
  case 0xD: {
    Instructions::display(this, args);
    break;
  }
  case 0xE: {
    decodeAndExecuteInputSkips(args);
    break;
  }
  default: {
    unknownOpCode(opCode, args);
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

void Chip8::reset() {
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
// ===== State of the System =========================
//

std::array<std::byte, 4 * KILOBYTE> Chip8::getMemory() const { return memory; }

const std::array<std::array<bool, DISPLAY_WIDTH>, DISPLAY_HEIGHT> &
Chip8::getDisplay() const {
  return display;
}

std::size_t Chip8::getPC() const { return PC; }

std::uint16_t Chip8::getI() const { return I; }

std::optional<std::uint16_t> Chip8::peekStack() const {
  return stack.empty() ? std::nullopt : std::make_optional(stack.back());
}

std::uint8_t Chip8::getRegister(size_t reg) const { return registers.at(reg); }

} // namespace chip8
