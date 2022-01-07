/**
 3XNN, 4XNN, 5XY0 and 9XY0 : Skip
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

//
// 3XNN: Skip if Equal to Immediate
//

TEST(SkipEqualImmSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<4>({
      0x6101, // load register 1 with 0x01
      0x3101, // Skip if register 1 == 0x01
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 3));
}

TEST(SkipEqualImmNoSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<4>({
      0x6102, // load register 1 with 0x02
      0x3101, // Skip if register 1 == 0x01
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 2));
}

//
// 4XNN: Skip if Not Equal to Immediate
//

TEST(SkipNotEqualImmSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<4>({
      0x6101, // load register 1 with 0x01
      0x4101, // Skip if register 1 != 0x01
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 2));
}

TEST(SkipNotEqualImmNoSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<4>({
      0x6102, // load register 1 with 0x02
      0x4101, // Skip if register 1 != 0x01
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<2>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 3));
}

//
// 5XY0: Skip if register VX and VY equal
//

TEST(SkipRegisterEqualSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<5>({
      0x6102, // load register 1 with 0x02
      0x6202, // load register 2 with 0x02
      0x5120, // Skip if register 1 == register 2
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<3>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 4));
}

TEST(SkipRegisterEqualNoSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<5>({
      0x6102, // load register 1 with 0x02
      0x6204, // load register 2 with 0x04
      0x5120, // Skip if register 1 == register 2
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<3>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 3));
}

//
// 9XY0: Skip if register VX and VY not equal
//

TEST(SkipRegisterNotEqualSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<5>({
      0x6102, // load register 1 with 0x02
      0x6203, // load register 2 with 0x03
      0x9120, // Skip if register 1 != register 2
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<3>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 4));
}

TEST(SkipRegisterNotEqualNoSkip, Skip) {
  auto chip8 = initChip8(romWithInstructions<5>({
      0x6102, // load register 1 with 0x02
      0x6202, // load register 2 with 0x02
      0x9120, // Skip if register 1 != register 2
      0x000F, // nop
      0x000F, // nop
  }));
  doNcycles<3>(chip8);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + (INSTRUCTION_BYTE_SIZE * 3));
}
