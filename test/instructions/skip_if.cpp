/**
 EX9E and EXA1 : Skip If Key Pressed
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

// TODO
// EX9E skip if pressed
// EXA1 skip if not pressed

TEST(SkipIf, SkipIf) {
  auto chip8 = initChip8();
  chip8.loadRom(romWithInstructions<2>({
      0xE09E, // skip if 0 pressed
      0x6001, // set register 0
  }));
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getRegister(0), 0x01);
}

TEST(SkipIfNot, SkipIf) {}
