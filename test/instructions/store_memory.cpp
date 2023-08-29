/**
 * FX55 : Store Memory
 */

#include <gtest/gtest.h>

#include "../helper.hpp"

TEST(Store1RegisterToMemory, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x120;
  auto chip8 = chip8AfterRunning<3>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6010,                      // set register 0 to 0x10
      0xF055,                      // Store Registers [0..0] to memory
  });
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart),
            static_cast<std::byte>(0x10));
}

TEST(Store5RegistersToMemory, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x200;
  auto chip8 = chip8AfterRunning<7>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6010,                      // set register 0 to 0x10
      0x6120,                      // set register 1 to 0x20
      0x6230,                      // set register 2 to 0x30
      0x6340,                      // set register 3 to 0x40
      0x6450,                      // set register 4 to 0x50
      0xF455,                      // Store Registers [0..5] to memory
  });
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 0),
            static_cast<std::byte>(0x10));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 1),
            static_cast<std::byte>(0x20));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 2),
            static_cast<std::byte>(0x30));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 3),
            static_cast<std::byte>(0x40));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 4),
            static_cast<std::byte>(0x50));
}

TEST(Store16RegistersToMemory, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x191;
  auto chip8 = chip8AfterRunning<18>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0x6010,                      // set register 0 to 0x10
      0x6120,                      // set register 1 to 0x20
      0x6230,                      // set register 2 to 0x30
      0x6340,                      // set register 3 to 0x40
      0x6450,                      // set register 4 to 0x50
      0x6560,                      // set register 5 to 0x60
      0x6670,                      // set register 6 to 0x70
      0x6780,                      // set register 7 to 0x80
      0x6890,                      // set register 8 to 0x90
      0x69A0,                      // set register 9 to 0xA0
      0x6AB0,                      // set register 10 to 0xB0
      0x6BC0,                      // set register 11 to 0xC0
      0x6CD0,                      // set register 12 to 0xD0
      0x6DE0,                      // set register 13 to 0xE0
      0x6EF0,                      // set register 14 to 0xF0
      0x6FFF,                      // set register 15 to 0xFF
      0xFF55,                      // Store Registers [0..15] to memory
  });

  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 0),
            static_cast<std::byte>(0x10));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 1),
            static_cast<std::byte>(0x20));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 2),
            static_cast<std::byte>(0x30));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 3),
            static_cast<std::byte>(0x40));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 4),
            static_cast<std::byte>(0x50));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 5),
            static_cast<std::byte>(0x60));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 6),
            static_cast<std::byte>(0x70));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 7),
            static_cast<std::byte>(0x80));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 8),
            static_cast<std::byte>(0x90));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 9),
            static_cast<std::byte>(0xA0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 10),
            static_cast<std::byte>(0xB0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 11),
            static_cast<std::byte>(0xC0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 12),
            static_cast<std::byte>(0xD0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 13),
            static_cast<std::byte>(0xE0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 14),
            static_cast<std::byte>(0xF0));
  EXPECT_EQ(chip8.getMemory().at(memoryStoreStart + 15),
            static_cast<std::byte>(0xFF));
}

TEST(CosmacIncrementsI, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x200;

  Chip8 chip8 = initChip8(romWithInstructions<2>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0xF355,                      // Store Registers [0..3] to memory
  }));
  chip8.config.configureAsCOSMACVIP();
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart + 4);
}

TEST(CosmacIncrementsIOneInstruction, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x200;

  Chip8 chip8 = initChip8(romWithInstructions<2>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0xF055,                      // Store Registers [0..0] to memory
  }));
  chip8.config.configureAsCOSMACVIP();
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart + 1);
}

TEST(Chip48DoesntIncrementI, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x200;

  Chip8 chip8 = initChip8(romWithInstructions<2>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0xF855,                      // Store Registers [0..8] to memory
  }));
  chip8.config.configureAsChip48();
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart);
}

TEST(SuperChipDoesntIncrementI, StoreMemory) {
  constexpr uint16_t memoryStoreStart = 0x200;

  Chip8 chip8 = initChip8(romWithInstructions<2>({
      (0xA000 + memoryStoreStart), // Set Index to `memoryStoreStart`
      0xF855,                      // Store Registers [0..8] to memory
  }));
  chip8.config.configureAsSuperCHIP();
  doNcycles<2>(chip8);

  EXPECT_EQ(chip8.getI(), memoryStoreStart);
}
