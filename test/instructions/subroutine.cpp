/**
 00EE and 2NNN: Subroutines
*/

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(SubroutinePush, Subroutine) {
  auto chip8 = chip8AfterRunning<1>({0x2ABC});

  EXPECT_EQ(chip8.peekStack(), ROM_START_ADDRESS + INSTRUCTION_BYTE_SIZE);
  EXPECT_EQ(chip8.getPC(), 0xABC);
}

TEST(SubroutinePushMultiple, Subroutine) {
  auto chip8 = initChip8(romWithInstructions<7>({
      0x2206, // push 206, the second push
      0x000F, // nop
      0x000F, // nop
      0x220C, // push 20C, the third push
      0x000F, // nop
      0x000F, // nop
      0X2FFF, // push FFF
  }));
  constexpr size_t START = ROM_START_ADDRESS;
  constexpr size_t STEP = INSTRUCTION_BYTE_SIZE;

  chip8.cycle();
  EXPECT_EQ(chip8.peekStack(), START + STEP);
  EXPECT_EQ(chip8.getPC(), START + (STEP * 3));
  chip8.cycle();
  EXPECT_EQ(chip8.peekStack(), START + (STEP * 3) + STEP);
  EXPECT_EQ(chip8.getPC(), START + (STEP * 6));
  chip8.cycle();
  EXPECT_EQ(chip8.peekStack(), START + (STEP * 6) + STEP);
  EXPECT_EQ(chip8.getPC(), 0xFFF);
}

TEST(SubroutinePop, Subroutine) {
  auto chip8 = initChip8(romWithInstructions<4>({
      0x2206, // push ABC
      0x000F, // nop
      0x000F, // nop
      0x00EE, // pop
  }));
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.peekStack(), std::nullopt);
  EXPECT_EQ(chip8.getPC(), ROM_START_ADDRESS + INSTRUCTION_BYTE_SIZE);
}
