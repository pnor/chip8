#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <cstdint>

#include "chip8.hpp"

namespace chip8 {

/** All instructions Chip8 can perform */
class Instructions {
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

  /** 8XY1 */
  static void binaryOR(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY2 */
  static void binaryAND(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY3 */
  static void binaryXOR(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY4 */
  static void addRegisters(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY5 */
  static void subtractYFromX(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY7 */
  static void subtractXFromY(Chip8 *const chip8, OpCodeArgs args);

  /** 8XY6 */
  static void shiftRightOne(Chip8 *const chip8, OpCodeArgs args);

  /** 8XYE */
  static void shiftLefttOne(Chip8 *const chip8, OpCodeArgs args);

  /** ANNN */
  static void setIndexRegisterI(Chip8 *const chip8, OpCodeArgs args);

  /** BNNN */
  static void jumpWithOffset(Chip8 *const chip8, OpCodeArgs args);

  /** CXNN */
  static void random(Chip8 *const chip8, OpCodeArgs args);

  /** DXYN */
  static void display(Chip8 *const chip8, OpCodeArgs args);

  /** EX9E */
  static void skipIfKeyPressed(Chip8 *const chip8, OpCodeArgs args);

  /** EXA1 */
  static void skipIfKeyNotPressed(Chip8 *const chip8, OpCodeArgs args);

  /** FX07 */
  static void setRegisterToDelayTimer(Chip8 *const chip8, OpCodeArgs args);

  /** FX15 */
  static void setDelayTimer(Chip8 *const chip8, OpCodeArgs args);

  /** FX18 */
  static void setSoundTimer(Chip8 *const chip8, OpCodeArgs args);

  /** FX1E */
  static void addToIndex(Chip8 *const chip8, OpCodeArgs args);

  /** FX0A  */
  static void getKey(Chip8 *const chip8, OpCodeArgs args);
};

} // namespace chip8

#endif // INSTRUCTION_H_
