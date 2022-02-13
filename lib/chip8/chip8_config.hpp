#ifndef CHIP8_CONFIG_H_
#define CHIP8_CONFIG_H_

class Chip8Config {
public:
  /** Defaults to the original COSMAC VIP*/
  Chip8Config();

  bool shiftUsesYRegister = false;
  bool jumpWithOffsetUsesV0 = false;

  void configureAsCOSMACVIP();
  void configureAsChip48();
  void configureAsSuperCHIP();
};

#endif // CHIP8_CONFIG_H_
