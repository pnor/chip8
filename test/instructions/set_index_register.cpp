/**
 * ANNN : Set Index Register
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SetIndex, SetIndex) {
  auto chip8 = chip8AfterRunning<1>({0xA123});
  EXPECT_EQ(chip8.getI(), 0x123);
}
