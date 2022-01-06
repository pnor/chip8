
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "array_rom.hpp"
#include "chip8.hpp"

using chip8::ArrayROM;
using chip8::Chip8;
using chip8::Chip8Interface;
using chip8::Instruction;
using std::array;
using std::make_unique;
using std::unique_ptr;

//
// Helper
//
static const std::function<void(chip8::Chip8 *chip8)> NOP_FUNC =
    [](chip8::Chip8 *) {};

chip8::Chip8 initChip8(std::unique_ptr<chip8::IROM> rom) {
  Chip8Interface interface(NOP_FUNC, NOP_FUNC);
  Chip8 chip8(interface);
  chip8.loadRom(std::move(rom));
  return chip8;
}

template <size_t N>
constexpr unique_ptr<ArrayROM<N>>
romWithInstructions(array<Instruction, N> instructions) {
  return make_unique<ArrayROM<N>>(instructions);
}

//
// Display
//

TEST(ClearScreenBlank, DisplayInstructions) {
  auto romPtr = romWithInstructions<1>({0x00E0});
  auto chip8 = initChip8(move(romPtr));
  chip8.cycle();

  const auto &display = chip8.getDisplay();
  for (const auto &row : display) {
    for (const auto &pixel : row) {
      EXPECT_FALSE(pixel);
    }
  }
}

TEST(ClearScreenDirty, DisplayInstructions) {
  auto romPtr = romWithInstructions<5>({
      0x6101, // load x register
      0x6201, // load y register
      0xA078, // set Index register
      0xD128, // draw
      0x00E0, // clear screen
  });

  auto chip8 = initChip8(move(romPtr));
  chip8.cycle();
  chip8.cycle();
  chip8.cycle();
  chip8.cycle();
  chip8.cycle();

  const auto &display = chip8.getDisplay();
  for (const auto &row : display) {
    for (const auto &pixel : row) {
      EXPECT_FALSE(pixel);
    }
  }
}
