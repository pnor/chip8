/**
 * 8XY4: Subtract Registers
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SubtractYFromXNoOverFlow, Subtract) {
  auto chip8 = chip8AfterRunning<3>({
      0x610A, // Set register 1 to 10 (X)
      0x6209, // Set register 2 to 9 (Y)
      0x8125  // Subtract
  });
  EXPECT_EQ(chip8.getRegister(1), 0x01);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}

TEST(SubtractYFromXOverFlow, Subtract) {
  auto chip8 = chip8AfterRunning<3>({
      0x6109, // Set register 1 to 9 (X)
      0x620A, // Set register 2 to 10 (Y)
      0x8125  // Subtract
  });
  EXPECT_EQ(chip8.getRegister(1), 0xFF);
  EXPECT_EQ(chip8.getRegister(0xF), 0);
}

TEST(SubtractXFromYNoOverFlow, Subtract) {
  auto chip8 = chip8AfterRunning<3>({
      0x6109, // Set register 1 to 9 (X)
      0x620A, // Set register 2 to 10 (Y)
      0x8127  // Subtract
  });
  EXPECT_EQ(chip8.getRegister(1), 0x01);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}

TEST(SubtractXFromYOverFlow, Subtract) {
  auto chip8 = chip8AfterRunning<3>({
      0x610A, // Set register 1 to 9 (X)
      0x6209, // Set register 2 to 10 (Y)
      0x8127  // Subtract
  });
  EXPECT_EQ(chip8.getRegister(1), 0xFF);
  EXPECT_EQ(chip8.getRegister(0xF), 0);
}
