#ifndef FILE_ROM_H_
#define FILE_ROM_H_

#include "irom.hpp"

namespace chip8 {
/** A ROM whose contents are loaded from a file */
class FileROM : public IROM {
private:
  std::ifstream file;

public:
  explicit FileROM(std::filesystem::path path);
  Instruction next() override;
  bool done() const override;
};

} // namespace chip8

#endif // FILE_ROM_H_
