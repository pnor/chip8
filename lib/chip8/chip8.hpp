#ifndef CHIP8_H_
#define CHIP8_H_

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "chip8_config.hpp"
#include "chip8_interface.hpp"

namespace chip8 {

constexpr static size_t KILOBYTE = 1024;
/** Instructions are 16 bits, with each part being 1 4 bit nibble */
using Instruction = std::uint16_t;
/** OP code is first 4 bits, a nibble */
using OpCode = std::uint8_t;
/** Remaining 12 bits are arguements for each op code. The first 4 bits
 * represneting which op code are always 0 */
using OpCodeArgs = std::uint16_t;
/** Address of the first instruction of the ROM */
constexpr size_t ROM_START_ADDRESS = 0x200;
/** Number of bytes 1 instruction takes */
constexpr size_t INSTRUCTION_BYTE_SIZE = 2;

/** Width of Chip8 Display */
constexpr size_t DISPLAY_WIDTH = 64;
/** Height of Chip8 Display */
constexpr size_t DISPLAY_HEIGHT = 32;

class IROM;

/** The CHIP-8 system */
class Chip8 {
private:
  /** 4 kilobytes of RAM */
  std::array<std::byte, KILOBYTE * 4> memory;

  /** Array of rows of the display, where first index is row, second column */
  std::array<std::array<bool, DISPLAY_WIDTH>, DISPLAY_HEIGHT> display;

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
  void decodeAndExecuteArithmetic(OpCodeArgs args);

  //
  // Convenience Functions
  //
  constexpr std::uint8_t &VF() { return registers[0xF]; }

  constexpr bool &displayAt(const size_t col, const size_t row) {
    return display.at(row).at(col);
  }

public:
  friend class Instructions;

  /** Number of CHIP-8 instructions emulated per second */
  size_t instructionsPerSecond = 700;
  /** Configuration of the system */
  Chip8Config config;

  explicit Chip8(Chip8Interface interface);

  //
  // Running Chip8 System
  //
  /** Load ROM into memory */
  bool loadRom(std::unique_ptr<IROM> rom);
  /** Perform one fetch/decode/execute cycle */
  void cycle();
  /** Run loaded ROM, starting the fetch/decode/execute infinite loop */
  void run();
  /** Resets chip8 to a state before any CPU cycles were performed and ROMS
   * loaded */
  void reset();

  //
  // Getting State of the System
  //
  std::array<std::byte, 4 * KILOBYTE> getMemory() const;
  const std::array<std::array<bool, DISPLAY_WIDTH>, DISPLAY_HEIGHT> &
  getDisplay() const;
  std::size_t getPC() const;
  std::uint16_t getI() const;
  std::optional<std::uint16_t> peekStack() const;
  std::uint8_t getRegister(size_t reg) const;
};

} // namespace chip8

#endif // CHIP8_H_
