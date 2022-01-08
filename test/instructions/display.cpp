/**
 * DXYN : Display
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

// Width of 8 pixels, so each line of a sprite is 1 byte

TEST(DrawGrid, Display) {
  constexpr std::uint16_t SPRITE_START =
      ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 2);
  auto chip8 = initChip8(romWithInstructions<3>(
      {(0xA000 + SPRITE_START), // Set Index to sprite location
       0xD002,                  // draw sprite
       // ----- The Sprite -----
       (0xAA00 + 0x0055)}));
  doNcycles<2>(chip8);
  const auto &display = chip8.getDisplay();

  auto pixelState = false;
  for (size_t i = 0; i < 2; i++) {
    pixelState = !pixelState;
    for (size_t j = 0; j < 8; j++) {
      EXPECT_EQ(display.at(i).at(j), pixelState);
      pixelState = !pixelState;
    }
  }
}

TEST(DrawPosition, Display) {
  constexpr std::uint16_t SPRITE_START =
      ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 4);
  auto chip8 = initChip8(romWithInstructions<5>(
      {(0xA000 + SPRITE_START), // Set Index to sprite location
       0x6001,                  // set 0 register to 1 for x
       0x6102,                  // set 1 register to 2 for y
       0xD012,                  // draw sprite
       // ----- The Sprite -----
       // X.X.X.X.
       // .X.X.X.X
       (0xAA00 + 0x0055)}));
  doNcycles<4>(chip8);
  const auto &display = chip8.getDisplay();

  auto pixelState = false;
  for (size_t i = 2; i < 4; i++) {
    pixelState = !pixelState;
    for (size_t j = 1; j < 9; j++) {
      EXPECT_EQ(display.at(i).at(j), pixelState);
      pixelState = !pixelState;
    }
  }
}

TEST(DrawXWrapping, Display) {
  constexpr std::uint16_t SPRITE_START =
      ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 4);
  auto chip8 = initChip8(romWithInstructions<5>(
      {(0xA000 + SPRITE_START), // Set Index to sprite location
       (0x6000 + chip8::DISPLAY_WIDTH -
        7),    // set 0 register so the last pixel is cut
       0x6100, // set 1 register to 0 for y
       0xD012, // draw sprite
       // ----- The Sprite -----
       // X.X.X.X.
       // .X.X.X.X
       (0xAA00 + 0x0055)}));
  doNcycles<4>(chip8);
  const auto &display = chip8.getDisplay();

  auto pixelState = false;
  for (size_t i = 0; i < 2; i++) {
    pixelState = !pixelState;
    for (size_t j = chip8::DISPLAY_WIDTH - 7; j < chip8::DISPLAY_WIDTH; j++) {
      EXPECT_EQ(display.at(i).at(j), pixelState);
      pixelState = !pixelState;
    }
  }
  EXPECT_EQ(display.at(0).at(0), false);
  EXPECT_EQ(display.at(1).at(0), false);
}
