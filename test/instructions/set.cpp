/**
 * 6XNN: Set
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SetOne, Set) {
  auto chip8 = chip8AfterRunning<1>({0x61FF});
  EXPECT_EQ(chip8.getRegister(1), 0xFF);
}

TEST(SetMultiple, Set) {
  auto chip8 = chip8AfterRunning<16>({
      0x6001, // set register  0
      0x6102, // set register  1
      0x6203, // set register  2
      0x6304, // set register  3
      0x6405, // set register  4
      0x6506, // set register  5
      0x6607, // set register  6
      0x6708, // set register  7
      0x6809, // set register  8
      0x690A, // set register  9
      0x6A0B, // set register 10
      0x6B0C, // set register 11
      0x6C0D, // set register 12
      0x6D0E, // set register 13
      0x6E0F, // set register 14
      0x6F10, // set register 15
  });
  auto baseVal = 0x01;
  for (size_t i = 0; i < 16; i++) {
    EXPECT_EQ(chip8.getRegister(i), baseVal++);
  }
}
