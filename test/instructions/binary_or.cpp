/**
 8XY1: Binary OR
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

using std::pair;
using std::vector;

TEST(BinaryOR, BinaryOR) {
  const vector<pair<uint8_t, uint8_t>> mathToCheck = {
      {0, 0}, {1, 1}, {12, 17}, {13, 47}, {183, 255},
  };
  auto chip8 = initChip8();
  for (const auto &numberPair : mathToCheck) {
    uint16_t firstRegisterVal = (0x6000 + numberPair.first);
    uint16_t secondRegisterVal = (0x6100 + numberPair.second);

    chip8.reset();
    chip8.loadRom(
        romWithInstructions<3>({firstRegisterVal,  // load first number
                                secondRegisterVal, // load second number
                                0x8011}));
    doNcycles<3>(chip8);

    EXPECT_EQ(chip8.getRegister(0), numberPair.first | numberPair.second);
  }
}
