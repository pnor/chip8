/**
 FX29 : Font Character
 */

#include <gtest/gtest.h>

#include "../helper.hpp"
#include "font.hpp"

TEST(FontCharacter, FontCharacter) {
  const auto chip8 = chip8AfterRunning<2>({
      0x6A01, // load register 0xA with 0x01
      0xFA29, // set index to register to font address
  });

  const auto memory = chip8.getMemory();
  for (size_t i = 0; i < chip8::FONT_BYTE_LENGTH; i++) {
    const auto memoryByte = memory[chip8.getI() + i];
    const auto fontByte = chip8::FONTS[1][i];
    EXPECT_EQ(memoryByte, fontByte);
  }
}

TEST(AllFonts, FontCharacter) {
  auto chip8 = initChip8(romWithInstructions<32>({
      0x6000, // load register 0 with 0x0
      0xF029, // set index to register to font address
      0x6001, // load register 0 with 0x1
      0xF029, // set index to register to font address
      0x6002, // load register 0 with 0x2
      0xF029, // set index to register to font address
      0x6003, // load register 0 with 0x3
      0xF029, // set index to register to font address
      0x6004, // load register 0 with 0x4
      0xF029, // set index to register to font address
      0x6005, // load register 0 with 0x5
      0xF029, // set index to register to font address
      0x6006, // load register 0 with 0x6
      0xF029, // set index to register to font address
      0x6007, // load register 0 with 0x7
      0xF029, // set index to register to font address
      0x6008, // load register 0 with 0x8
      0xF029, // set index to register to font address
      0x6009, // load register 0 with 0x9
      0xF029, // set index to register to font address
      0x600A, // load register 0 with 0xA
      0xF029, // set index to register to font address
      0x600B, // load register 0 with 0xB
      0xF029, // set index to register to font address
      0x600C, // load register 0 with 0xC
      0xF029, // set index to register to font address
      0x600D, // load register 0 with 0xD
      0xF029, // set index to register to font address
      0x600E, // load register 0 with 0xE
      0xF029, // set index to register to font address
      0x600F, // load register 0 with 0xF
      0xF029, // set index to register to font address
  }));

  for (int i = 0; i < 16; i++) {
    doNcycles<2>(chip8);
    const auto memory = chip8.getMemory();
    for (size_t j = 0; j < chip8::FONT_BYTE_LENGTH; j++) {
      const auto memoryByte = memory[chip8.getI() + j];
      const auto fontByte = chip8::FONTS[i][j];
      EXPECT_EQ(memoryByte, fontByte);
    }
  }
}
