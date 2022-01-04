#ifndef ARRAY_ROM_H_
#define ARRAY_ROM_H_

#include "irom.hpp"

namespace chip8 {

/** A ROM whose contents are hard coded in the form of an array */
template <size_t N> class ArrayROM : public IROM {
private:
  const std::array<Instruction, N> instructions;
  size_t instructionIndex = 0;

public:
  explicit ArrayROM(std::array<Instruction, N> instructions)
      : instructions(instructions) {}

  Instruction next() override { return instructions.at(instructionIndex++); }

  bool done() const override { return instructionIndex >= N; }
};

} // namespace chip8

#endif // ARRAY_ROM_H_
