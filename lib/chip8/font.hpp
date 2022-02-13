#ifndef FONT_H_
#define FONT_H_

#include <cstddef>

namespace chip8 {
using FontData = std::byte[5];
constexpr size_t FONT_BYTE_LENGTH = 5;
constexpr size_t NUM_FONTS = 16;

/** Write `font` to memory starting at `memPtr` */
constexpr void writeFontToMemory(std::byte *memPtr, const FontData font) {
  for (size_t i = 0; i < FONT_BYTE_LENGTH; i++) {
    memPtr[i] = font[i];
  }
}

const FontData FONTS[NUM_FONTS] = {
    // 0
    {std::byte(0xF0), std::byte(0x90), std::byte(0x90), std::byte(0x90),
     std::byte(0xF0)},
    // 1
    {std::byte(0x20), std::byte(0x60), std::byte(0x20), std::byte(0x20),
     std::byte(0x70)},
    // 2
    {std::byte(0xF0), std::byte(0x10), std::byte(0xF0), std::byte(0x80),
     std::byte(0xF0)},
    // 3
    {std::byte(0xF0), std::byte(0x10), std::byte(0xF0), std::byte(0x10),
     std::byte(0xF0)},
    // 4
    {std::byte(0x90), std::byte(0x90), std::byte(0xF0), std::byte(0x10),
     std::byte(0x10)},
    // 5
    {std::byte(0xF0), std::byte(0x80), std::byte(0xF0), std::byte(0x10),
     std::byte(0xF0)},
    // 6
    {std::byte(0xF0), std::byte(0x80), std::byte(0xF0), std::byte(0x90),
     std::byte(0xF0)},
    // 7
    {std::byte(0xF0), std::byte(0x10), std::byte(0x20), std::byte(0x40),
     std::byte(0x40)},
    // 8
    {std::byte(0xF0), std::byte(0x90), std::byte(0xF0), std::byte(0x90),
     std::byte(0xF0)},
    // 9
    {std::byte(0xF0), std::byte(0x90), std::byte(0xF0), std::byte(0x10),
     std::byte(0xF0)},
    // A
    {std::byte(0xF0), std::byte(0x90), std::byte(0xF0), std::byte(0x90),
     std::byte(0x90)},
    // B
    {std::byte(0xE0), std::byte(0x90), std::byte(0xE0), std::byte(0x90),
     std::byte(0xE0)},
    // C
    {std::byte(0xF0), std::byte(0x80), std::byte(0x80), std::byte(0x80),
     std::byte(0xF0)},
    // D
    {std::byte(0xE0), std::byte(0x90), std::byte(0x90), std::byte(0x90),
     std::byte(0xE0)},
    // E
    {std::byte(0xF0), std::byte(0x80), std::byte(0xF0), std::byte(0x80),
     std::byte(0xF0)},
    // F
    {std::byte(0xF0), std::byte(0x80), std::byte(0xF0), std::byte(0x80),
     std::byte(0x80)},
};

} // namespace chip8

#endif // FONT_H_
