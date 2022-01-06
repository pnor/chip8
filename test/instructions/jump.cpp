/**
 1NNN: Jump
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(Jump, Jump) {
  auto chip8 = chip8AfterRunning<1>({0x1000});
  EXPECT_EQ(chip8.getPC(), 0);
  chip8.reset();

  chip8.loadRom(romWithInstructions<1>({0x1FFF}));
  chip8.cycle();
  EXPECT_EQ(chip8.getPC(), 0xFFF);
  chip8.reset();

  chip8.loadRom(romWithInstructions<1>({0x10A0}));
  chip8.cycle();
  EXPECT_EQ(chip8.getPC(), 0x0A0);
  chip8.reset();

  chip8.loadRom(romWithInstructions<1>({0x1ABC}));
  chip8.cycle();
  EXPECT_EQ(chip8.getPC(), 0xABC);
}
