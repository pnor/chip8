/**
 * FX65 : Load Memory
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(Laod1RegisterToMemory, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<6>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6020,                      // set register 0 to 0x20
      0xF055,                      // Store Registers [0..0] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0xF065,                      // Load Registers [0..0] to memory
  });
  EXPECT_EQ(chip8.getRegister(0), static_cast<uint8_t>(0x20));
}

TEST(Load5RegistersToMemory, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<14>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 0 to 0x01
      0x6102,                      // set register 1 to 0x02
      0x6203,                      // set register 2 to 0x03
      0x6304,                      // set register 3 to 0x04
      0x6405,                      // set register 4 to 0x05
      0xF455,                      // Store Registers [0..4] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0x6100,                      // set register 1 to 0x00
      0x6200,                      // set register 2 to 0x00
      0x6300,                      // set register 3 to 0x00
      0x6400,                      // set register 4 to 0x00
      0xF465,                      // Load Registers [0..4] to memory
  });
  EXPECT_EQ(chip8.getRegister(0), static_cast<uint8_t>(0x01));
  EXPECT_EQ(chip8.getRegister(1), static_cast<uint8_t>(0x02));
  EXPECT_EQ(chip8.getRegister(2), static_cast<uint8_t>(0x03));
  EXPECT_EQ(chip8.getRegister(3), static_cast<uint8_t>(0x04));
  EXPECT_EQ(chip8.getRegister(4), static_cast<uint8_t>(0x05));
}

TEST(Load16RegistersToMemory, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<36>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 00 to 0x01
      0x6102,                      // set register 01 to 0x02
      0x6203,                      // set register 02 to 0x03
      0x6304,                      // set register 03 to 0x04
      0x6405,                      // set register 04 to 0x05
      0x6506,                      // set register 05 to 0x06
      0x6607,                      // set register 06 to 0x07
      0x6708,                      // set register 07 to 0x08
      0x6809,                      // set register 08 to 0x09
      0x690A,                      // set register 09 to 0x0A
      0x6A0B,                      // set register 10 to 0x0B
      0x6B0C,                      // set register 11 to 0x0C
      0x6C0D,                      // set register 12 to 0x0D
      0x6D0E,                      // set register 13 to 0x0E
      0x6E0F,                      // set register 14 to 0x0F
      0x6F10,                      // set register 15 to 0x10
      0xFF55,                      // Store Registers [0..15] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 00 to 0x00
      0x6100,                      // set register 01 to 0x00
      0x6200,                      // set register 02 to 0x00
      0x6300,                      // set register 03 to 0x00
      0x6400,                      // set register 04 to 0x00
      0x6500,                      // set register 05 to 0x00
      0x6600,                      // set register 06 to 0x00
      0x6700,                      // set register 07 to 0x00
      0x6800,                      // set register 08 to 0x00
      0x6900,                      // set register 09 to 0x00
      0x6A00,                      // set register 10 to 0x00
      0x6B00,                      // set register 11 to 0x00
      0x6C00,                      // set register 12 to 0x00
      0x6D00,                      // set register 13 to 0x00
      0x6E00,                      // set register 14 to 0x00
      0x6F00,                      // set register 15 to 0x00
      0xFF65,                      // Load Registers [0..15] to memory
  });
  EXPECT_EQ(chip8.getRegister(0), static_cast<uint8_t>(0x01));
  EXPECT_EQ(chip8.getRegister(1), static_cast<uint8_t>(0x02));
  EXPECT_EQ(chip8.getRegister(2), static_cast<uint8_t>(0x03));
  EXPECT_EQ(chip8.getRegister(3), static_cast<uint8_t>(0x04));
  EXPECT_EQ(chip8.getRegister(4), static_cast<uint8_t>(0x05));
  EXPECT_EQ(chip8.getRegister(5), static_cast<uint8_t>(0x06));
  EXPECT_EQ(chip8.getRegister(6), static_cast<uint8_t>(0x07));
  EXPECT_EQ(chip8.getRegister(7), static_cast<uint8_t>(0x08));
  EXPECT_EQ(chip8.getRegister(8), static_cast<uint8_t>(0x09));
  EXPECT_EQ(chip8.getRegister(9), static_cast<uint8_t>(0x0A));
  EXPECT_EQ(chip8.getRegister(10), static_cast<uint8_t>(0x0B));
  EXPECT_EQ(chip8.getRegister(11), static_cast<uint8_t>(0x0C));
  EXPECT_EQ(chip8.getRegister(12), static_cast<uint8_t>(0x0D));
  EXPECT_EQ(chip8.getRegister(13), static_cast<uint8_t>(0x0E));
  EXPECT_EQ(chip8.getRegister(14), static_cast<uint8_t>(0x0F));
  EXPECT_EQ(chip8.getRegister(15), static_cast<uint8_t>(0x10));
}

TEST(CosmacIncrementsI, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<14>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 0 to 0x01
      0x6102,                      // set register 1 to 0x02
      0x6203,                      // set register 2 to 0x03
      0x6304,                      // set register 3 to 0x04
      0x6405,                      // set register 4 to 0x05
      0xF455,                      // Store Registers [0..4] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0x6100,                      // set register 1 to 0x00
      0x6200,                      // set register 2 to 0x00
      0x6300,                      // set register 3 to 0x00
      0x6400,                      // set register 4 to 0x00
      0xF465,                      // Load Registers [0..4] to memory
  });
  EXPECT_EQ(chip8.getI(), memoryStoreStart + 5);
}

TEST(CosmacIncrementsIOneInstruction, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<14>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 0 to 0x01
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0xF065,                      // Load Registers [0..4] to memory
  });
  EXPECT_EQ(chip8.getI(), memoryStoreStart + 1);
}

TEST(Chip48DoesntIncrementI, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = initChip8(romWithInstructions<14>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 0 to 0x01
      0x6102,                      // set register 1 to 0x02
      0x6203,                      // set register 2 to 0x03
      0x6304,                      // set register 3 to 0x04
      0x6405,                      // set register 4 to 0x05
      0xF455,                      // Store Registers [0..4] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0x6100,                      // set register 1 to 0x00
      0x6200,                      // set register 2 to 0x00
      0x6300,                      // set register 3 to 0x00
      0x6400,                      // set register 4 to 0x00
      0xF465,                      // Load Registers [0..4] to memory
  }));
  chip8.config.configureAsChip48();
  doNcycles<14>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart);
}

TEST(SuperChipDoesntIncrementI, LoadMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = initChip8(romWithInstructions<14>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6001,                      // set register 0 to 0x01
      0x6102,                      // set register 1 to 0x02
      0x6203,                      // set register 2 to 0x03
      0x6304,                      // set register 3 to 0x04
      0x6405,                      // set register 4 to 0x05
      0xF455,                      // Store Registers [0..4] to memory
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6000,                      // set register 0 to 0x00
      0x6100,                      // set register 1 to 0x00
      0x6200,                      // set register 2 to 0x00
      0x6300,                      // set register 3 to 0x00
      0x6400,                      // set register 4 to 0x00
      0xF465,                      // Load Registers [0..4] to memory
  }));
  chip8.config.configureAsSuperCHIP();
  doNcycles<14>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart);
}
