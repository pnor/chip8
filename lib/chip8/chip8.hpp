#ifndef CHIP8_H_
#define CHIP8_H_

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "chip8_interface.hpp"

namespace chip8 {

constexpr static size_t KILOBYTE = 1024;
/** Instructions are 16 bits, with each part being 1 4 bit nibble */
using Instruction = std::uint16_t;
/** OP code is first 4 bits, a nibble */
using OpCode = std::uint8_t;
/** Remaining 12 bits are arguements for each op code */
using OpCodeArgs = std::uint16_t;

/** The CHIP-8 system */
class Chip8 {
private:
  /** 4 kilobytes of RAM */
  std::array<std::byte, KILOBYTE * 4> memory;

  /** 64 x 32 monochrome pixels */
  constexpr static size_t DISPLAY_WIDTH = 64;
  constexpr static size_t DISPLAY_HEIGHT = 32;
  std::array<std::array<bool, DISPLAY_HEIGHT>, DISPLAY_WIDTH> display;

  /** Program Counter */
  std::size_t PC;

  /** Index register */
  std::uint16_t I;

  /** Stack for 16 bit addresses */
  std::vector<std::uint16_t> stack;
  const size_t stackLimit = 12;

  /** 8 bit delay timer */
  std::uint8_t delayTimer;

  /** 8 bit sound timer */
  std::uint8_t soundTimer;

  /** 16 8-bit (one byte) general purpose variable registers */
  constexpr static size_t NUM_REGISTERS = 16;
  std::array<std::uint8_t, NUM_REGISTERS> registers;

  //
  // Interface
  //
  Chip8Interface interface;

  //
  // Helper Functions
  //

  /** Store font data in memory from 0x50 to 0x9F */
  void setupFonts();
  Instruction fetch();
  void decodeAndExecute(Instruction instruction);

public:
  friend class Instructions;

  /** Number of CHIP-8 instructions emulated per second */
  size_t instructionsPerSecond = 700;

  explicit Chip8(Chip8Interface interface);

  //
  // Running Chip8 System
  //
  /** Load ROM into memory */
  void loadRom();
  /** Run loaded ROM, starting the fetch/decode/execute loop */
  void run();

  //
  // Getting State of the System
  //
  std::array<std::byte, 4 * KILOBYTE> dumpMemory();
  const std::array<std::array<bool, DISPLAY_HEIGHT>, DISPLAY_WIDTH> &
  getDisplay();
};

} // namespace chip8

#endif // CHIP8_H_
