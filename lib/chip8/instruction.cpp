#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>

#include "instruction.hpp"

namespace chip8 {

using std::uint8_t;
//
// Helper
//
constexpr bool bitFromByte(size_t bitNumber, std::uint8_t byte) {
  assert(bitNumber < 8);
  return (byte >> bitNumber) & 0x01;
}

//
// Instruction
//

void Instructions::executeMachineLanguageRoutine(Chip8 *const chip8,
                                                 OpCodeArgs args) {
  std::cout << "unimplemented\n" << std::endl;
}

void Instructions::clearScreen(Chip8 *const chip8, OpCodeArgs args) {
  for (size_t i = 0; i < chip8->display.size(); i++) {
    std::fill(chip8->display[i].begin(), chip8->display[i].end(), false);
  }
  // TODO call display hook?
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
  uint8_t x = (chip8->registers.at(xArg)) % Chip8::DISPLAY_WIDTH;
  uint8_t y = (chip8->registers.at(yArg)) % Chip8::DISPLAY_HEIGHT;
  VF(chip8) = 0;

  const auto &I = chip8->I;

  const uint8_t N = (args & 0x000F);
  for (uint8_t i = 0;
       i < std::min(Chip8::DISPLAY_HEIGHT, static_cast<size_t>(N));
       i++) { // row
    const uint8_t nthSpriteData = static_cast<uint8_t>(chip8->memory.at(I + N));
    for (uint8_t j = 0; j < Chip8::DISPLAY_WIDTH / 8; j++) { // col

      // loop through each pixel in the byte
      for (size_t k = 0; k < 8; i++) {
        const auto spriteBit = bitFromByte(k, nthSpriteData);
        if (spriteBit == 0) {
          continue;
        }

        if (spriteBit == displayAt(chip8, y, x)) {
          VF(chip8) = 1;
        } else {
          displayAt(chip8, y, x) = 1;
        }
      }
      x++;
    }
    y++;
  }

} // namespace chip8
