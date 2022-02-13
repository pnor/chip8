/**
 * CXNN : Random
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

/** Number of times to keep running the random function call to find errors */
static const int numberRandomTries = 20;

/** Returns true if `value` is in [`low`, `high`] inclusively */
constexpr bool isBetween(uint8_t value, uint8_t low, uint8_t high) {
  return low <= value && value <= high;
}

/** Returns true if `value` is in `values` */
template <size_t N>
constexpr bool isOneOf(uint8_t value, std::array<uint8_t, N> values) {
  return std::find(values.begin(), values.end(), value);
}

TEST(Random, Random) {
  auto chip8 = chip8AfterRunning<1>({0xC0FF});
  EXPECT_TRUE(isBetween(chip8.getRegister(0),
                        std::numeric_limits<uint8_t>::min(),
                        std::numeric_limits<uint8_t>::max()));
}

TEST(RandomAnding, Random) {
  auto chip8 = initChip8();

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC000}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isBetween(chip8.getRegister(0), 0, 0));
    chip8.reset();
  }

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC001}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isOneOf<2>(chip8.getRegister(0), {0, 1}));
    chip8.reset();
  }

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC002}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isOneOf<2>(chip8.getRegister(0), {0, 2}));
    chip8.reset();
  }

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC00F}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isBetween(chip8.getRegister(0), 0, 15));
    chip8.reset();
  }

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC00F}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isBetween(chip8.getRegister(0), 0, 15));
    chip8.reset();
  }

  for (int i = 0; i < numberRandomTries; i++) {
    chip8.loadRom(romWithInstructions<1>({0xC009}));
    doNcycles<1>(chip8);
    EXPECT_TRUE(isOneOf<4>(chip8.getRegister(0), {0, 1, 8, 9}));
    chip8.reset();
  }
}
