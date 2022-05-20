#include "key_code.hpp"

std::optional<KeyCode> intToKeyCode(const unsigned int val) {
  if (val > 17) {
    return std::nullopt;
  }
  return std::make_optional<KeyCode>(static_cast<KeyCode>(val));
}
