#include "chip8_config.hpp"

#include <random>

Chip8Config::Chip8Config() { configureAsCOSMACVIP(); }

unsigned int Chip8Config::randomSeed() const { return _randomSeed; }

void Chip8Config::configureAsCOSMACVIP() {
  shiftUsesYRegister = true;
  jumpWithOffsetUsesV0 = true;
}

void Chip8Config::configureAsChip48() {
  shiftUsesYRegister = false;
  jumpWithOffsetUsesV0 = false;
}

void Chip8Config::configureAsSuperCHIP() {
  shiftUsesYRegister = false;
  jumpWithOffsetUsesV0 = false;
}

void Chip8Config::setRandomSeed(unsigned int seed) {
  _randomSeed = seed;
  std::srand(_randomSeed);
}
