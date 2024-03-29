#include <algorithm>
#include <cassert>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>

#include "font.hpp"
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

constexpr uint8_t getXFrom0X00(OpCodeArgs args) { return (args & 0x0F00) >> 8; }

constexpr uint8_t getYFrom00Y0(OpCodeArgs args) { return (args & 0x00F0) >> 4; }

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
  std::vector<uint16_t> &stack = chip8->stack;
  assert(!stack.empty());
  chip8->PC = stack.back();
  stack.pop_back();
}

void Instructions::skipIfEqualImmediate(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t imm = args & 0x00FF;
  uint8_t reg = getXFrom0X00(args);
  if (chip8->registers.at(reg) == imm) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfNotEqualImmediate(Chip8 *const chip8,
                                           OpCodeArgs args) {
  const uint8_t imm = args & 0x00FF;
  uint8_t reg = getXFrom0X00(args);
  if (chip8->registers.at(reg) != imm) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfRegistersEqual(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  if (chip8->registers.at(regX) == chip8->registers.at(regY)) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfRegistersNotEqual(Chip8 *const chip8,
                                           OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  if (chip8->registers.at(regX) != chip8->registers.at(regY)) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::setRegister(Chip8 *const chip8, const OpCodeArgs args) {
  uint8_t reg = getXFrom0X00(args);
  uint8_t value = args & 0x00FF;
  chip8->registers.at(reg) = value;
}

void Instructions::addValueToRegister(Chip8 *const chip8, OpCodeArgs args) {
  uint8_t reg = getXFrom0X00(args);
  uint8_t value = args & 0x00FF;
  chip8->registers.at(reg) += value;
}

void Instructions::setRegisterXToY(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  chip8->registers.at(regX) = chip8->registers.at(regY);
}

void Instructions::binaryOR(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  chip8->registers.at(regX) |= chip8->registers.at(regY);
}

void Instructions::binaryAND(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  chip8->registers.at(regX) &= chip8->registers.at(regY);
}

void Instructions::binaryXOR(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  chip8->registers.at(regX) ^= chip8->registers.at(regY);
}

void Instructions::addRegisters(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  const uint16_t xVal = chip8->registers.at(regX);
  const uint16_t yVal = chip8->registers.at(regY);
  const uint16_t result = xVal + yVal;
  if (result > 255) {
    chip8->registers.at(0xF) = 1;
    chip8->registers.at(regX) =
        chip8->registers.at(regX) + chip8->registers.at(regY);
  } else {
    chip8->registers.at(regX) = result;
  }
}

void Instructions::subtractYFromX(Chip8 *const chip8, OpCodeArgs args) {
  chip8->registers.at(0xF) = 1;
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  if (chip8->registers.at(regY) > chip8->registers.at(regX)) {
    chip8->VF() = 0;
  }
  chip8->registers.at(regX) =
      chip8->registers.at(regX) - chip8->registers.at(regY);
}

void Instructions::subtractXFromY(Chip8 *const chip8, OpCodeArgs args) {
  chip8->registers.at(0xF) = 1;
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t regY = getYFrom00Y0(args);
  if (chip8->registers.at(regX) > chip8->registers.at(regY)) {
    chip8->VF() = 0;
  }
  chip8->registers.at(regX) =
      chip8->registers.at(regY) - chip8->registers.at(regX);
}

void Instructions::shiftRightOne(Chip8 *const chip8, OpCodeArgs args) {
  if (chip8->config.shiftUsesYRegister) {
    // Store X in Y and set flag to bit shifted out, then shift
    const uint8_t regX = getXFrom0X00(args);
    const uint8_t regY = getYFrom00Y0(args);
    chip8->registers.at(regY) = chip8->registers.at(regX);
    auto bitShiftedOut = chip8->registers.at(regX) & 0x01;
    chip8->VF() = bitShiftedOut;
    chip8->registers.at(regX) >>= 1;
  } else {
    // Shift VX in place
    const uint8_t regX = getXFrom0X00(args);
    chip8->registers.at(regX) >>= 1;
  }
  // Use Flag and VY register

  // Super8 and chip48 (shift VX in place)
}

void Instructions::shiftLefttOne(Chip8 *const chip8, OpCodeArgs args) {
  if (chip8->config.shiftUsesYRegister) {
    // Store X in Y and set flag to bit shifted out, then shift
    const uint8_t regX = getXFrom0X00(args);
    const uint8_t regY = getYFrom00Y0(args);
    chip8->registers.at(regY) = chip8->registers.at(regX);
    auto bitShiftedOut = (chip8->registers.at(regX) & 0x80) >> 7;
    chip8->VF() = bitShiftedOut;
    chip8->registers.at(regX) <<= 1;
  } else {
    // Shift VX in place
    const uint8_t regX = getXFrom0X00(args);
    chip8->registers.at(regX) <<= 1;
  }
}

void Instructions::setIndexRegisterI(Chip8 *const chip8, OpCodeArgs args) {
  chip8->I = args;
}

void Instructions::jumpWithOffset(Chip8 *const chip8, OpCodeArgs args) {
  if (chip8->config.jumpWithOffsetUsesV0) {
    const uint8_t imm = args & 0x0FFF;
    chip8->PC = imm + chip8->getRegister(0);
  } else {
    const size_t imm = args & 0x0FFF;
    const uint8_t regX = getXFrom0X00(args);
    chip8->PC = imm + chip8->getRegister(regX);
  }
}

void Instructions::random(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t mask = args & 0x00FF;
  uint8_t random = rand() % std::numeric_limits<uint8_t>::max();
  chip8->registers.at(regX) = random & mask;
}

void Instructions::display(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t xArg = getXFrom0X00(args);
  const uint8_t yArg = getYFrom00Y0(args);
  uint8_t x = (chip8->registers.at(xArg)) % DISPLAY_WIDTH;
  uint8_t y = (chip8->registers.at(yArg)) % DISPLAY_HEIGHT;
  chip8->VF() = 0;

  const auto &I = chip8->I;

  const uint8_t N = args & 0x000F;
  const size_t byteSize = std::min(DISPLAY_HEIGHT, static_cast<size_t>(N));

  for (uint8_t i = 0; i < byteSize; i++) {
    const uint8_t spriteByte = static_cast<uint8_t>(chip8->memory.at(I + i));
    auto tempX = x;
    for (uint8_t j = 0; j < 8; j++) {
      if (tempX >= DISPLAY_WIDTH) {
        break;
      }

      const bool spriteBit = bitFromByte(7 - j, spriteByte);
      const auto oldBit = chip8->displayAt(tempX, y);
      chip8->displayAt(tempX, y) = chip8->displayAt(tempX, y) ^ spriteBit;
      // if bit was unset, detect the collision
      if (oldBit && !chip8->displayAt(tempX, y)) {
        chip8->VF() = 1;
      }
      tempX++;
    }
    y++;
    if (y >= DISPLAY_HEIGHT) {
      break;
    }
  }
  chip8->interface.callDisplayHook(chip8);
}

void Instructions::skipIfKeyPressed(Chip8 *const chip8, OpCodeArgs args) {
  const unsigned int key = getXFrom0X00(args);
  const auto keyCode = intToKeyCode(key);

  if (keyCode.has_value() && chip8->input()->pollKeyState(keyCode.value())) {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::skipIfKeyNotPressed(Chip8 *const chip8, OpCodeArgs args) {
  const unsigned int key = getXFrom0X00(args);
  const std::optional<KeyCode> keyCode = intToKeyCode(key);
  if (keyCode.has_value()) {
    if (!chip8->input()->pollKeyState(keyCode.value())) {
      chip8->PC += INSTRUCTION_BYTE_SIZE;
    }
  } else {
    chip8->PC += INSTRUCTION_BYTE_SIZE;
  }
}

void Instructions::setRegisterToDelayTimer(Chip8 *const chip8,
                                           OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  chip8->registers.at(regX) = chip8->delayTimer;
}

void Instructions::setDelayTimer(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  chip8->delayTimer = chip8->registers.at(regX);
}

void Instructions::setSoundTimer(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  chip8->soundTimer = chip8->registers.at(regX);
}

void Instructions::addToIndex(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const auto newI = chip8->I + chip8->registers.at(regX);
  if (newI > 0x0FFF) {
    chip8->VF() = 1;
  }
  chip8->I = newI;
}

void Instructions::getKey(Chip8 *const chip8, OpCodeArgs args) {
  const std::optional<KeyCode> key = chip8->input()->keyPressed();
  if (key == std::nullopt) {
    chip8->PC -= INSTRUCTION_BYTE_SIZE;
  } else {
    const uint8_t regX = getXFrom0X00(args);
    chip8->registers.at(regX) = static_cast<uint8_t>(key.value());
  }
}

void Instructions::fontCharacter(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  const uint8_t character = chip8->registers.at(regX) & 0x0F;
  chip8->I = FONT_START_ADDRESS + (FONT_BYTE_LENGTH * character);
}

void Instructions::binaryCodedDecimalConversion(Chip8 *const chip8,
                                                OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  uint8_t value = chip8->registers.at(regX);
  const auto I = chip8->I;
  auto &memory = chip8->memory;
  // X..
  const uint8_t lastDigit = value / 100;
  memory[I] = static_cast<std::byte>(lastDigit);
  value -= lastDigit * 100;
  // .X.
  const uint8_t middleDigit = value / 10;
  memory[I + 1] = static_cast<std::byte>(middleDigit);
  value -= middleDigit * 10;
  // ..X
  memory[I + 2] = static_cast<std::byte>(value);
}

void Instructions::storeMemory(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  auto &I = chip8->I;
  auto &memory = chip8->memory;

  if (chip8->config.storeAndLoadMemoryIncrementsI) {
    for (uint8_t i = 0; i <= regX; i++) {
      memory[I] = static_cast<std::byte>(chip8->registers.at(i));
      I++;
    }
  } else {
    for (uint8_t i = 0; i <= regX; i++) {
      memory[I + i] = static_cast<std::byte>(chip8->registers.at(i));
    }
  }
}

void Instructions::loadMemory(Chip8 *const chip8, OpCodeArgs args) {
  const uint8_t regX = getXFrom0X00(args);
  auto &I = chip8->I;
  const auto &memory = chip8->memory;

  if (chip8->config.storeAndLoadMemoryIncrementsI) {
    for (uint8_t i = 0; i <= regX; i++) {
      chip8->registers.at(i) = static_cast<uint8_t>(memory[I]);
      I++;
    }
  } else {
    for (uint8_t i = 0; i <= regX; i++) {
      chip8->registers.at(i) = static_cast<uint8_t>(memory[I + i]);
    }
  }
}

} // namespace chip8
