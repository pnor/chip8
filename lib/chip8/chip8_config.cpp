#include "chip8_config.hpp"

Chip8Config::Chip8Config() { configureAsCOSMACVIP(); }

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
