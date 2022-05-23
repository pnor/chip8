/**
 FX33 : Binary-coded Decimal Conversion
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(BinaryCodedDecimalConversion, BinaryCodedDecimalConversion) {
  const auto chip8 = chip8AfterRunning<2>({
      0x6A7B, // load register 0xA with 0x7B (123 in decimal)
      0xFA33, // Binary-coded Decimal Conversion
  });

  const auto memory = chip8.getMemory();
  EXPECT_EQ(memory[chip8.getI() + 0], std::byte(1));
  EXPECT_EQ(memory[chip8.getI() + 1], std::byte(2));
  EXPECT_EQ(memory[chip8.getI() + 2], std::byte(3));
}

TEST(SingleDigit, BinaryCodedDecimalConversion) {
  const auto chip8 = chip8AfterRunning<2>({
      0x6A07, // load register 0xA with 0x7
      0xFA33, // Binary-coded Decimal Conversion
  });

  const auto memory = chip8.getMemory();
  EXPECT_EQ(memory[chip8.getI() + 0], std::byte(0));
  EXPECT_EQ(memory[chip8.getI() + 1], std::byte(0));
  EXPECT_EQ(memory[chip8.getI() + 2], std::byte(7));
}

TEST(DoubleDigit, BinaryCodedDecimalConversion) {
  const auto chip8 = chip8AfterRunning<2>({
      0x6F31, // load register 0xF with 0x31 (49 in decimal)
      0xFF33, // Binary-coded Decimal Conversion
  });

  const auto memory = chip8.getMemory();
  EXPECT_EQ(memory[chip8.getI() + 0], std::byte(0));
  EXPECT_EQ(memory[chip8.getI() + 1], std::byte(4));
  EXPECT_EQ(memory[chip8.getI() + 2], std::byte(9));
}

TEST(Zero, BinaryCodedDecimalConversion) {
  const auto chip8 = chip8AfterRunning<2>({
      0x6C00, // load register 0xC with 0
      0xFC33, // Binary-coded Decimal Conversion
  });

  const auto memory = chip8.getMemory();
  EXPECT_EQ(memory[chip8.getI() + 0], std::byte(0));
  EXPECT_EQ(memory[chip8.getI() + 1], std::byte(0));
  EXPECT_EQ(memory[chip8.getI() + 2], std::byte(0));
}

TEST(Max, BinaryCodedDecimalConversion) {
  const auto chip8 = chip8AfterRunning<2>({
      0x60FF, // load register 0x0 with 0xFF (255)
      0xF033, // Binary-coded Decimal Conversion
  });

  const auto memory = chip8.getMemory();
  EXPECT_EQ(memory[chip8.getI() + 0], std::byte(2));
  EXPECT_EQ(memory[chip8.getI() + 1], std::byte(5));
  EXPECT_EQ(memory[chip8.getI() + 2], std::byte(5));
}
