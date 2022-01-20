/**
 00E0: Clear Screen
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(ClearScreenBlank, ClearScreen) {
  auto chip8 = chip8AfterRunning<1>({0x00E0});

  const auto &display = chip8.getDisplay();
  for (const auto &row : display) {
    for (const auto &pixel : row) {
      EXPECT_FALSE(pixel);
    }
  }
}

TEST(ClearScreenDirty, ClearScreen) {
  auto chip8 = chip8AfterRunning<5>({
      0x6101, // load x register
      0x6201, // load y register
      0xA078, // set Index register
      0xD128, // draw
      0x00E0, // clear screen
  });

  const auto &display = chip8.getDisplay();
  for (const auto &row : display) {
    for (const auto &pixel : row) {
      EXPECT_FALSE(pixel);
    }
  }
}
