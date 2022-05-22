/**
 FX0A : Get Key
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(GetKey, GetKey) {
  auto input = TestInput::inputWithKeyPressed(KeyCode::KEY_1);
  auto chip8 = initChip8(std::nullopt, std::move(input));
  chip8.loadRom(romWithInstructions<1>({
      0xF00A // get key
  }));
  doNcycles<1>(chip8);

  EXPECT_EQ(chip8.getRegister(0), 0x01);
}

TEST(GetKeyDifferentRegister, GetKey) {
  auto input = TestInput::inputWithKeyPressed(KeyCode::KEY_A);
  auto chip8 = initChip8(std::nullopt, std::move(input));
  chip8.loadRom(romWithInstructions<1>({
      0xFC0A // get key
  }));
  doNcycles<1>(chip8);

  EXPECT_EQ(chip8.getRegister(0xC), 0x0A);
}

TEST(GetKeyBlocks, GetKey) {
  auto input = TestInput::inputWithNoKeyPressed();
  auto chip8 = initChip8(std::nullopt, std::move(input));
  chip8.loadRom(romWithInstructions<3>({
      0xF10A, // get key
      0x60FF, // load register 0 with 0xFF
      0x61FF, // load register 1 with 0xFF
  }));
  doNcycles<3>(chip8);

  EXPECT_EQ(chip8.getRegister(0), 0);
  EXPECT_EQ(chip8.getRegister(1), 0);
}
