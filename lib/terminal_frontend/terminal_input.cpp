#include <format>
#include <ncurses.h>
#include <unordered_map>

#include "terminal_input.hpp"

static const std::unordered_map<int, KeyCode> valueToKeyCode = {
    // 0 .. 9
    {48, KeyCode::KEY_0},
    {49, KeyCode::KEY_1},
    {50, KeyCode::KEY_2},
    {51, KeyCode::KEY_3},
    {52, KeyCode::KEY_4},
    {53, KeyCode::KEY_5},
    {54, KeyCode::KEY_6},
    {55, KeyCode::KEY_7},
    {56, KeyCode::KEY_8},
    {57, KeyCode::KEY_9},
    // A .. F
    {65, KeyCode::KEY_A},
    {66, KeyCode::KEY_B},
    {67, KeyCode::KEY_C},
    {68, KeyCode::KEY_D},
    {69, KeyCode::KEY_E},
    {70, KeyCode::KEY_F},
    // a .. f
    {97, KeyCode::KEY_A},
    {98, KeyCode::KEY_B},
    {99, KeyCode::KEY_C},
    {100, KeyCode::KEY_D},
    {101, KeyCode::KEY_E},
    {102, KeyCode::KEY_F},
    // F1
    {265, KeyCode::KEY_F1},
    // F2
    {266, KeyCode::KEY_F2},
};

bool TerminalInput::pollKeyState(const KeyCode code) {
  const int keypress = getch();
  const auto mapResult = valueToKeyCode.find(keypress);
  return mapResult != valueToKeyCode.end() && mapResult->second == code;
}

std::optional<KeyCode> TerminalInput::keyPressed() {
  const int keypress = getch();
  const auto mapResult = valueToKeyCode.find(keypress);
  return mapResult == valueToKeyCode.end()
             ? std::nullopt
             : std::make_optional(mapResult->second);
}
