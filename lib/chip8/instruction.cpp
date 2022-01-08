#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>

#include "instruction.hpp"

namespace chip8 {

using std::uint8_t;

//
// ===== Helper ===============
//

constexpr bool bitFromByte(size_t bitNumber, std::uint8_t byte) {
  assert(bitNumber < 8);
  return (byte >> bitNumber) & 0x01;
}

//
// ===== Instruction ===============
//

void Instructions::executeMachineLanguageRoutine(Chip8 *const chip8,
                                                 OpCodeArgs args) {
  std::cout << "unimplemented\n" << std::endl;
}

void Instructions::clearScreen(Chip8 *const chip8, OpCodeArgs args) {
  for (size_t i = 0; i < chip8->display.size(); i++) {
    std::fill(chip8->display[i].begin(), chip8->display[i].end(), false);
  }
  chip8->interface.callDisplayHook(chip8);
}

void Instructions::jump(Chip8 *const chip8, OpCodeArgs args) {
  chip8->PC = args;
}

void Instructions::pushSubroutine(Chip8 *const chip8, OpCodeArgs args) {
  chip8->stack.push_back(chip8->PC);
  chip8->PC = args;
}

void Instructions::popSubroutine(Chip8 *const chip8, OpCodeArgs args) {
  auto &stack = chip8->stack;
  assert(!stack.empty());
  chip8->PC = stack.back();
  stack.pop_back();
}

void Instructions::skipIfEqualImmediate(Chip8 *const chip8, OpCodeArgs args) {
  // TODO test these
  const uint8_t imm = args & 0x00FF;
  uint8_t reg = (args & 0x0F00) >> 8;
  if (chip8->registers.at(reg) == imm) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfNotEqualImmediate(Chip8 *const chip8,
                                           OpCodeArgs args) {
  const uint8_t imm = args & 0x00FF;
  uint8_t reg = (args & 0x0F00) >> 8;
  if (chip8->registers.at(reg) != imm) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfRegistersEqual(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = (args & 0x0F00) >> 8;
  const uint8_t regY = (args & 0x00F0) >> 4;
  if (chip8->registers.at(regX) == chip8->registers.at(regY)) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfRegistersNotEqual(Chip8 *const chip8,
                                           OpCodeArgs args) {
  const uint8_t regX = (args & 0x0F00) >> 8;
  const uint8_t regY = (args & 0x00F0) >> 4;
  if (chip8->registers.at(regX) != chip8->registers.at(regY)) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::setRegister(Chip8 *const chip8, const OpCodeArgs args) {
  uint8_t reg = (args & 0x0F00) >> 8;
  uint8_t value = args & 0x00FF;
  chip8->registers.at(reg) += value;
}

void Instructions::addValueToRegister(Chip8 *const chip8, OpCodeArgs args) {
  uint8_t reg = (args & 0x0F00) >> 8;
  uint8_t value = args & 0x00FF;
  chip8->registers.at(reg) += value;
}

void Instructions::setIndexRegisterI(Chip8 *const chip8, OpCodeArgs args) {
  chip8->I = args;
}

void Instructions::display(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t xArg = (args & 0x0F00) >> 8;
  const uint8_t yArg = (args & 0x00F0) >> 4;
  uint8_t x = (chip8->registers.at(xArg)) % DISPLAY_WIDTH;
  uint8_t y = (chip8->registers.at(yArg)) % DISPLAY_HEIGHT;
  VF(chip8) = 0;

  const auto &I = chip8->I;

  const uint8_t N = args & 0x000F;
  const size_t byteSize = std::min(DISPLAY_HEIGHT, static_cast<size_t>(N));

  for (uint8_t i = 0; i < byteSize; i++) {
    const uint8_t spriteByte = static_cast<uint8_t>(chip8->memory.at(I + i));
    auto tempX = x;
    for (uint8_t j = 0; j < 8; j++) {
      const bool spriteBit = bitFromByte(7 - j, spriteByte);
      const auto oldBit = displayAt(chip8, tempX, y);
      displayAt(chip8, tempX, y) = displayAt(chip8, tempX, y) ^ spriteBit;
      // if bit was unset, detect the collision
      if (oldBit && !displayAt(chip8, tempX, y)) {
        VF(chip8) = 1;
      }
      tempX++;
    }
    y++;
  }
  chip8->interface.callDisplayHook(chip8);
}

} // namespace chip8
