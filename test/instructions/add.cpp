/**
 * 7XNN: Add
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(Add, Add) {
  auto chip8 = chip8AfterRunning<1>({0x7101});
  EXPECT_EQ(chip8.getRegister(1), 0x01);
}

TEST(AddOnePlusTwo, Add) {
  auto chip8 = chip8AfterRunning<2>({
      0x6101, // Set register 1 to 1
      0x7102  // Add 2 to register 1
  });
  EXPECT_EQ(chip8.getRegister(1), 0x03);
}

TEST(AddNoCarry, Add) {
  auto chip8 = chip8AfterRunning<2>({
      0x61FF, // Set register 1 to 0xFF
      0x7101  // Add 1 to register 1 (to overflow)
  });
  EXPECT_EQ(chip8.getRegister(1), 0);
  EXPECT_EQ(chip8.getRegister(0xF), 0);

  chip8.reset();
  chip8.loadRom(romWithInstructions<3>({
      0x6F01, // Set VF to 1
      0x61FF, // Set register 1 to 0xFF
      0x7101  // Add 1 to register 1 (to overflow)
  }));
  doNcycles<3>(chip8);
  EXPECT_EQ(chip8.getRegister(1), 0);
  EXPECT_EQ(chip8.getRegister(0xF), 1);
}
