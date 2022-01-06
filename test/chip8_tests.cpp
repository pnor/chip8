#include <gtest/gtest.h>
#include <iostream>

#include "chip8.hpp"
#include "helper.hpp"

// Demonstrate some basic assertions.
using std::byte;

TEST(Chip8SystemTests, FontInit) {
  auto interface =
      chip8::Chip8Interface([](chip8::Chip8 *) {}, [](chip8::Chip8 *) {});
  auto chip8 = chip8::Chip8(interface);
  auto memory = chip8.getMemory();
  // 0
  EXPECT_EQ(memory[0x50 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x50 + 1], byte(0x90));
  EXPECT_EQ(memory[0x50 + 2], byte(0x90));
  EXPECT_EQ(memory[0x50 + 3], byte(0x90));
  EXPECT_EQ(memory[0x50 + 4], byte(0xF0));
  // 1
  EXPECT_EQ(memory[0x55 + 0], byte(0x20));
  EXPECT_EQ(memory[0x55 + 1], byte(0x60));
  EXPECT_EQ(memory[0x55 + 2], byte(0x20));
  EXPECT_EQ(memory[0x55 + 3], byte(0x20));
  EXPECT_EQ(memory[0x55 + 4], byte(0x70));
  // 2
  EXPECT_EQ(memory[0x5A + 0], byte(0xF0));
  EXPECT_EQ(memory[0x5A + 1], byte(0x10));
  EXPECT_EQ(memory[0x5A + 2], byte(0xF0));
  EXPECT_EQ(memory[0x5A + 3], byte(0x80));
  EXPECT_EQ(memory[0x5A + 4], byte(0xF0));
  // 3
  EXPECT_EQ(memory[0x5F + 0], byte(0xF0));
  EXPECT_EQ(memory[0x5F + 1], byte(0x10));
  EXPECT_EQ(memory[0x5F + 2], byte(0xF0));
  EXPECT_EQ(memory[0x5F + 3], byte(0x10));
  EXPECT_EQ(memory[0x5F + 4], byte(0xF0));
  // 4
  EXPECT_EQ(memory[0x64 + 0], byte(0x90));
  EXPECT_EQ(memory[0x64 + 1], byte(0x90));
  EXPECT_EQ(memory[0x64 + 2], byte(0xF0));
  EXPECT_EQ(memory[0x64 + 3], byte(0x10));
  EXPECT_EQ(memory[0x64 + 4], byte(0x10));
  // 5
  EXPECT_EQ(memory[0x69 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x69 + 1], byte(0x80));
  EXPECT_EQ(memory[0x69 + 2], byte(0xF0));
  EXPECT_EQ(memory[0x69 + 3], byte(0x10));
  EXPECT_EQ(memory[0x69 + 4], byte(0xF0));
  // 6
  EXPECT_EQ(memory[0x6E + 0], byte(0xF0));
  EXPECT_EQ(memory[0x6E + 1], byte(0x80));
  EXPECT_EQ(memory[0x6E + 2], byte(0xF0));
  EXPECT_EQ(memory[0x6E + 3], byte(0x90));
  EXPECT_EQ(memory[0x6E + 4], byte(0xF0));
  // 7
  EXPECT_EQ(memory[0x73 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x73 + 1], byte(0x10));
  EXPECT_EQ(memory[0x73 + 2], byte(0x20));
  EXPECT_EQ(memory[0x73 + 3], byte(0x40));
  EXPECT_EQ(memory[0x73 + 4], byte(0x40));
  // 8
  EXPECT_EQ(memory[0x78 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x78 + 1], byte(0x90));
  EXPECT_EQ(memory[0x78 + 2], byte(0xF0));
  EXPECT_EQ(memory[0x78 + 3], byte(0x90));
  EXPECT_EQ(memory[0x78 + 4], byte(0xF0));
  // 9
  EXPECT_EQ(memory[0x7D + 0], byte(0xF0));
  EXPECT_EQ(memory[0x7D + 1], byte(0x90));
  EXPECT_EQ(memory[0x7D + 2], byte(0xF0));
  EXPECT_EQ(memory[0x7D + 3], byte(0x10));
  EXPECT_EQ(memory[0x7D + 4], byte(0xF0));
  // A
  EXPECT_EQ(memory[0x82 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x82 + 1], byte(0x90));
  EXPECT_EQ(memory[0x82 + 2], byte(0xF0));
  EXPECT_EQ(memory[0x82 + 3], byte(0x90));
  EXPECT_EQ(memory[0x82 + 4], byte(0x90));
  // B
  EXPECT_EQ(memory[0x87 + 0], byte(0xE0));
  EXPECT_EQ(memory[0x87 + 1], byte(0x90));
  EXPECT_EQ(memory[0x87 + 2], byte(0xE0));
  EXPECT_EQ(memory[0x87 + 3], byte(0x90));
  EXPECT_EQ(memory[0x87 + 4], byte(0xE0));
  // C
  EXPECT_EQ(memory[0x8C + 0], byte(0xF0));
  EXPECT_EQ(memory[0x8C + 1], byte(0x80));
  EXPECT_EQ(memory[0x8C + 2], byte(0x80));
  EXPECT_EQ(memory[0x8C + 3], byte(0x80));
  EXPECT_EQ(memory[0x8C + 4], byte(0xF0));
  // D
  EXPECT_EQ(memory[0x91 + 0], byte(0xE0));
  EXPECT_EQ(memory[0x91 + 1], byte(0x90));
  EXPECT_EQ(memory[0x91 + 2], byte(0x90));
  EXPECT_EQ(memory[0x91 + 3], byte(0x90));
  EXPECT_EQ(memory[0x91 + 4], byte(0xE0));
  // E
  EXPECT_EQ(memory[0x96 + 0], byte(0xF0));
  EXPECT_EQ(memory[0x96 + 1], byte(0x80));
  EXPECT_EQ(memory[0x96 + 2], byte(0xF0));
  EXPECT_EQ(memory[0x96 + 3], byte(0x80));
  EXPECT_EQ(memory[0x96 + 4], byte(0xF0));
  // F
  EXPECT_EQ(memory[0x9B + 0], byte(0xF0));
  EXPECT_EQ(memory[0x9B + 1], byte(0x80));
  EXPECT_EQ(memory[0x9B + 2], byte(0xF0));
  EXPECT_EQ(memory[0x9B + 3], byte(0x80));
  EXPECT_EQ(memory[0x9B + 4], byte(0x80));
}

TEST(Chip8SystemTests, Reset) {
  auto interface =
      chip8::Chip8Interface([](chip8::Chip8 *) {}, [](chip8::Chip8 *) {});
  auto chip8 = chip8::Chip8(interface);
  // TODO
}
