#ifndef KEY_CODE_H_
#define KEY_CODE_H_

#include <optional>

/** Possible Ipnuts to Chip8 include 0-9, A-F, and F1, F2 */
enum KeyCode {
  KEY_0 = 0x0u,
  KEY_1 = 0x1u,
  KEY_2 = 0x2u,
  KEY_3 = 0x3u,
  KEY_4 = 0x4u,
  KEY_5 = 0x5u,
  KEY_6 = 0x6u,
  KEY_7 = 0x7u,
  KEY_8 = 0x8u,
  KEY_9 = 0x9u,
  KEY_A = 0xAu,
  KEY_B = 0xBu,
  KEY_C = 0xCu,
  KEY_D = 0xDu,
  KEY_E = 0xEu,
  KEY_F = 0xFu,
  KEY_F1 = 16u,
  KEY_F2 = 17u,
};

std::optional<KeyCode> intToKeyCode(const unsigned int val);

#endif // KEY_CODE_H_
