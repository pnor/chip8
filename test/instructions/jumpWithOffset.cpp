/**
   BNNN: Jump with Offset
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

// TEST(JumpWithOffsetUsingV0, JumpWithOffset) {
//   auto chip8 = initChip8(romWithInstructions<2>({
//       0x6010, // Set register 0 to 16
//       0xB00F, // Jump with Offset
//   }));
//   chip8.config.jumpWithOffsetUsesV0 = true;
//   doNcycles<2>(chip8);
//   EXPECT_EQ(chip8.getPC(), 0xF + 0x10);
// }

TEST(JumpWithOffsetNoV0, JumpWithOffset) {
  auto chip8 = initChip8(romWithInstructions<2>({
      0x6010, // Set register 1 to 16
      0xB00F, // Jump with Offset
  }));
  chip8.config.jumpWithOffsetUsesV0 = false;
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), 0xF + 0x10);
  chip8.reset();

  chip8.loadRom(romWithInstructions<2>({
      0x6505, // Set register 5 to 5
      0xB500, // Jump with Offset
  }));
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), 0x500 + 0x5);
}
