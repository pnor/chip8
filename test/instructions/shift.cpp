/**
 * 8XY6 and 8XYE: Right and Left Shift
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

//
// Shift Right
//

TEST(ShiftRight, Shift) {
  auto chip8 = chip8AfterRunning<2>({
      0x6102, // Set register 1 to 2
      0x8126, // Shift right
  });
  EXPECT_EQ(chip8.getRegister(1), 0x02 >> 1);
}

TEST(ShiftRightWithYShiftOut1, Shift) {
  auto chip8 = initChip8(romWithInstructions<2>({
      0x6103, // Set register 1 to 3
      0x8126, // Shift right
  }));
  chip8.config.shiftUsesYRegister = true;
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getRegister(1), 1);
  EXPECT_EQ(chip8.getRegister(2), 3);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}

TEST(ShiftRightWithYShiftOut0, Shift) {
  auto chip8 = initChip8(romWithInstructions<2>({
      0x6102, // Set register 1 to 2
      0x8126, // Shift right
  }));
  chip8.config.shiftUsesYRegister = true;
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getRegister(1), 1);
  EXPECT_EQ(chip8.getRegister(2), 2);
  EXPECT_EQ(chip8.getRegister(0xF), 0);
}

//
// Shift Left
//

TEST(ShiftLeft, Shift) {
  auto chip8 = chip8AfterRunning<2>({
      0x6101, // Set register 1 to 1
      0x812E, // Shift left
  });
  EXPECT_EQ(chip8.getRegister(1), 0x01 << 1);
}

TEST(ShiftLeftWithYShiftOut1, Shift) {
  auto chip8 = initChip8(romWithInstructions<2>({
      0x61FF, // Set register 1 to 255
      0x812E, // Shift right
  }));
  chip8.config.shiftUsesYRegister = true;
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getRegister(1), 0xFE);
  EXPECT_EQ(chip8.getRegister(2), 0xFF);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}

TEST(ShiftLeftWithYShiftOut0, Shift) {
  auto chip8 = initChip8(romWithInstructions<2>({
      0x6102, // Set register 1 to 2
      0x812E, // Shift right
  }));
  chip8.config.shiftUsesYRegister = true;
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getRegister(1), 4);
  EXPECT_EQ(chip8.getRegister(2), 2);
  EXPECT_EQ(chip8.getRegister(0xF), 0);
}
