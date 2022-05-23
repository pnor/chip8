/**
   FX1E: Add to index
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(AddToIndex, AddToIndex) {
  auto chip8 = chip8AfterRunning<2>({
      0x60DE, // Set register 0 to 0xDE
      0xF01E, // Add register 0 to Index
  });

  EXPECT_EQ(chip8.getI(), 0xDE);
}

TEST(AddToIndexOverflows, AddToIndex) {
  auto chip8 = chip8AfterRunning<3>({
      0xAFFF, // Set Index to 0xFFF
      0x6001, // Set register 0 to 0x01
      0xF01E, // Add register 0 to Index
  });

  EXPECT_EQ(chip8.getRegister(0xF), 1);
}
