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
  /** 0NNN */
  static void executeMachineLanguageRoutine(Chip8 *const chip8,
                                            OpCodeArgs args);

  /** 00E0 */
  static void clearScreen(Chip8 *const chip8, OpCodeArgs args);

  /** 1NNN */
  static void jump(Chip8 *const chip8, OpCodeArgs args);

  /** 2NNN */
  static void pushSubroutine(Chip8 *const chip8, OpCodeArgs args);

  /** 00EE */
  static void popSubroutine(Chip8 *const chip8, OpCodeArgs args);

  /** 3XNN */
  static void skipIfEqualImmediate(Chip8 *const chip8, OpCodeArgs args);

  /** 4XNN */
  static void skipIfNotEqualImmediate(Chip8 *const chip8, OpCodeArgs args);

  /** 5XY0 */
  static void skipIfRegistersEqual(Chip8 *const chip8, OpCodeArgs args);

  /** 9XY0 */
  static void skipIfRegistersNotEqual(Chip8 *const chip8, OpCodeArgs args);

  /** 6XNN */
  static void setRegister(Chip8 *const chip8, const OpCodeArgs args);

  /** 7XNN */
  static void addValueToRegister(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY0 */
  static void setRegisterXToY(Chip8 *const chip8, OpCodeArgs args);

  /** ANNN */
  static void setIndexRegisterI(Chip8 *const chip8, OpCodeArgs args);

  /** DXYN */
  static void display(Chip8 *const chip8, OpCodeArgs args);
};

} // namespace chip8

#endif // INSTRUCTION_H_
