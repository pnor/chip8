#ifndef ROM_H_
#define ROM_H_

#include "chip8.hpp"

#include <filesystem>
#include <fstream>

namespace chip8 {

/** ROM of a Chip8, a sequence of opcodes loaded into memory */
class IROM {
public:
  /** Get next instruction from the ROM */
  virtual Instruction next() = 0;
  /** True if all instructions have been read */
  virtual bool done() const = 0;
  virtual ~IROM() = default;
};

} // namespace chip8
#endif // ROM_H_
