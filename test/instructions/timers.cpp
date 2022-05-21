/**
   FX07, FX15, and FX18 : Timers
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SetRegisterToDelayTimer, SetRegisterToDelayTimer) {
  auto chip8 = chip8AfterRunning<2>({
      0x6010, // set register 0 to 10
      0xF007, // set register 0 to delay timer
  });

  EXPECT_EQ(chip8.getRegister(0), 0x00);
}

TEST(SetRegisterToDelayTimerNonZeroTimer, SetRegisterToDelayTimer) {
  auto chip8 = chip8AfterRunning<4>({
      0x6010, // set register 0 to 10
      0xF015, // set delay timer to register 0
      0x6000, // set register 0 to 0
      0xF007, // set register 0 to delay timer
  });

  EXPECT_EQ(chip8.getDelayTimer(), 0x10);
}

TEST(SetDelayTimerToRegister, SetDelayTimerToRegister) {
  auto chip8 = chip8AfterRunning<2>({
      0x600B, // set register 0 to 0xB
      0xF015  // set delay timer to register 0
  });

  EXPECT_EQ(chip8.getDelayTimer(), 0x0B);
}

TEST(SetSoundTimer, SetSoundTimer) {
  auto chip8 = chip8AfterRunning<2>({
      0x6A0E, // set register 0 to 0xE
      0xFA18  // set sound timer to register 0
  });

  EXPECT_EQ(chip8.getSoundTimer(), 0x0E);
}
