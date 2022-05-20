#ifndef KEY_CODE_H_
#define KEY_CODE_H_

#include <optional>

/** Possible Ipnuts to Chip8 include 0-9, A-F, and F1, F2 */
enum KeyCode {
  KEY_0 = 0,
  KEY_1 = 1,
  KEY_2 = 2,
  KEY_3 = 3,
  KEY_4 = 4,
  KEY_5 = 5,
  KEY_6 = 6,
  KEY_7 = 7,
  KEY_8 = 8,
  KEY_9 = 9,
  KEY_A = 10,
  KEY_B = 11,
  KEY_C = 12,
  KEY_D = 13,
  KEY_E = 14,
  KEY_F = 15,
  KEY_F1 = 16,
  KEY_F2 = 17,
};

std::optional<KeyCode> intToKeyCode(const unsigned int val);

#endif // KEY_CODE_H_
