/**
 * 8XY0 : Set Register X to Register Y
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SetRegisters, SetRegisterXToY) {
  auto chip8 = chip8AfterRunning<3>({
      0x6100, // set 1 to 0x0
      0x62FF, // set 2 to 0xFF
      0x8120, // set 1 to 2
  });
  EXPECT_EQ(chip8.getRegister(1), 0xFF);
}
