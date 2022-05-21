/**
   FX07, FX15, and FX18 : Timers
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SetDelayTimer, SetDelayTimer) {
  auto chip8 = chip8AfterRunning<2>({
      0x6010, // set register 0 to 10
      0xF007  // set delay timer to register 0
  });

  EXPECT_EQ(chip8.getDelayTimer(), 0x10);
}
