/**
 * 8XY4: Add Registers
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(AddRegisters, AddRegisters) {
  auto chip8 = chip8AfterRunning<3>({
      0x6101, // Set register 1 to 1
      0x6202, // Set register 2 to 2
      0x8124, // Add register 1 and 2
  });
  EXPECT_EQ(chip8.getRegister(1), 0x03);
  EXPECT_EQ(chip8.getRegister(0xF), 0);
}

TEST(AddRegistersOverflow, AddRegisters) {
  auto chip8 = chip8AfterRunning<3>({
      0x61FF, // Set register 1 to 255
      0x6202, // Set register 2 to 1
      0x8124, // Add register 1 and 2
  });
  EXPECT_EQ(chip8.getRegister(1), 1);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}
