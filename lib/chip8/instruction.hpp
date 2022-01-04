#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <cstdint>

#include "chip8.hpp"

namespace chip8 {

/** All instructions Chip8 can perform */
class Instructions {
private:
  static constexpr std::uint8_t &VF(Chip8 *const chip8) {
    return chip8->registers[0xF];
  }

  static constexpr bool &displayAt(Chip8 *const chip8, const size_t col,
                                   const size_t row) {
    return chip8->display.at(row).at(col);
  }

public:
  static void executeMachineLanguageRoutine(Chip8 *const chip8,
                                            OpCodeArgs args);

  static void clearScreen(Chip8 *const chip8, OpCodeArgs args);

  static void jump(Chip8 *const chip8, OpCodeArgs args);

  static void pushSubroutine(Chip8 *const chip8, OpCodeArgs args);

  static void popSubroutine(Chip8 *const chip8, OpCodeArgs args);

  static void skipIfEqualImmediate(Chip8 *const chip8, OpCodeArgs args);

  static void skipIfNotEqualImmediate(Chip8 *const chip8, OpCodeArgs args);

  static void skipIfRegistersEqual(Chip8 *const chip8, OpCodeArgs args);

  static void skipIfRegistersNotEqual(Chip8 *const chip8, OpCodeArgs args);

  static void setRegister(Chip8 *const chip8, const OpCodeArgs args);

  static void addValueToRegister(Chip8 *const chip8, OpCodeArgs args);

  static void setIndexRegisterI(Chip8 *const chip8, OpCodeArgs args);

  static void display(Chip8 *const chip8, OpCodeArgs args);
};

} // namespace chip8

#endif // INSTRUCTION_H_
