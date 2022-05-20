#include "helper.hpp"

bool TestInput::pollKeyState(const KeyCode key) {
  return this->pollFunction(key);
}

TestInput::TestInput(InputFunction pollFunction) {
  this->pollFunction = pollFunction;
}

unique_ptr<TestInput> TestInput::inputWithKeyPressed(const KeyCode key) {
  const InputFunction keyPollFunction = [key](const KeyCode code) {
    return code == key;
  };
  return unique_ptr<TestInput>(new TestInput(keyPollFunction));
}

unique_ptr<TestInput> TestInput::inputWithNoKeyPressed() {
  const InputFunction noKeyFunction = [](const KeyCode code) { return false; };
  return unique_ptr<TestInput>(new TestInput(noKeyFunction));
}

Chip8 initChip8(std::optional<std::unique_ptr<chip8::IROM>> rom,
                std::optional<std::unique_ptr<IInput>> input) {
  std::unique_ptr<IInput> interfaceInput;
  if (input.has_value()) {
    interfaceInput = std::move(input.value());
  } else {
    interfaceInput = TestInput::inputWithNoKeyPressed();
  }

  chip8::Chip8Interface interface(std::move(interfaceInput), NOP_FUNC,
                                  NOP_FUNC);
  Chip8 chip8(std::move(interface));
  if (rom.has_value()) {
    chip8.loadRom(std::move(rom.value()));
  }
  chip8.config.setRandomSeed(0);
  return chip8;
}
