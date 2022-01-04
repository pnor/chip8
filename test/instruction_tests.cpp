
#include <gtest/gtest.h>
#include <iostream>

#include "chip8.hpp"

//
// Helper
//
chip8::Chip8 initChip8(std::unique_ptr<chip8::IROM> rom) {
  // TODO
}

//
// Display
//

TEST(ClearScreen, DisplayInstructions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
