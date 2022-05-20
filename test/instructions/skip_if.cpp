/**
 EX9E and EXA1 : Skip If Key Pressed
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

// TODO
// EX9E skip if pressed
// EXA1 skip if not pressed

TEST(SkipIf, SkipIf) {
  auto input = TestInput::inputWithKeyPressed(KeyCode::KEY_0);
  auto chip8 = initChip8(std::nullopt, std::move(input));
  chip8.loadRom(romWithInstructions<3>({
      0xE09E, // skip if 0 pressed
      0x6001, // set register 0
      0x6101, // set register 1
  }));
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getRegister(0), 0x00);
  EXPECT_EQ(chip8.getRegister(1), 0x01);
}

TEST(SkipIfNoSkip, SkipIf) {
  auto input = TestInput::inputWithKeyPressed(KeyCode::KEY_1);
  auto chip8 = initChip8(std::nullopt, std::move(input));
  chip8.loadRom(romWithInstructions<3>({
      0xE09E, // skip if 0 pressed
      0x6001, // set register 0
      0x6101, // set register 1
  }));
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getRegister(0), 0x01);
  EXPECT_EQ(chip8.getRegister(1), 0x00);
}

TEST(SkipIfNot, SkipIf) {}