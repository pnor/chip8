/**
 * FX55 : Store Memory
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

// stores 1 register correctly
TEST(Store1RegisterToMemory, StoreMemory) {
  const uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<3>({
      (0xA000 + memoryStoreStart), // Set Index to 0x120
      0x6010,                      // set register 0 to 0x10
      0xF055,                      // Store Registers [0..0] to memory
  });
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart),
            static_cast<std::byte>(0x10));
}

// stores 5 register correctly
// stores 16 register correctly
// on cosmac, increments I
// on chip48, doesnt I
// on superchip8, doesnt I
