#ifndef HELPER_H_
#define HELPER_H_

#include <memory>

#include "array_rom.hpp"
#include "chip8.hpp"
#include "key_code.hpp"

using chip8::ArrayROM;
using chip8::Chip8;
using chip8::Instruction;
using std::array;
using std::make_unique;
using std::unique_ptr;

using InputFunction = std::function<bool(const KeyCode code)>;

constexpr size_t ROM_START_ADDRESS = 0x200;
constexpr size_t INSTRUCTION_BYTE_SIZE = 2;

const std::function<void(chip8::Chip8 *chip8)> NOP_FUNC = [](chip8::Chip8 *) {};

class TestInput : public IInput {
public:
  virtual bool pollKeyState(const KeyCode code) override;

  /** `key` is the Key that is always pressed */
  static unique_ptr<TestInput> inputWithKeyPressed(const KeyCode key);
  /** Create Input that never has any key pressed */
  static unique_ptr<TestInput> inputWithNoKeyPressed();

private:
  InputFunction pollFunction;

  TestInput(InputFunction pollFunction);
};

Chip8 initChip8(std::optional<std::unique_ptr<chip8::IROM>> rom = std::nullopt,
                std::optional<std::unique_ptr<IInput>> input = std::nullopt);

template <size_t N>
constexpr unique_ptr<ArrayROM<N>>
romWithInstructions(array<Instruction, N> instructions) {
  return make_unique<ArrayROM<N>>(instructions);
}

template <size_t N>
Chip8 chip8AfterRunning(array<Instruction, N> instructions) {
  auto chip8 = initChip8(romWithInstructions<N>(instructions));
  for (size_t i = 0; i < N; i++) {
    chip8.cycle();
  }
  return chip8;
}

template <size_t N> void doNcycles(Chip8 &chip8) {
  for (size_t i = 0; i < N; i++) {
    chip8.cycle();
  }
}
#endif // HELPER_H_
