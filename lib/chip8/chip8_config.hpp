#ifndef CHIP8_CONFIG_H_
#define CHIP8_CONFIG_H_

#include <time.h>

class Chip8Config {
public:
  /** Defaults to the original COSMAC VIP*/
  Chip8Config();

  bool shiftUsesYRegister = false;
  bool jumpWithOffsetUsesV0 = false;

  unsigned int randomSeed() const;

  void configureAsCOSMACVIP();
  void configureAsChip48();
  void configureAsSuperCHIP();
  void setRandomSeed(unsigned int seed);

private:
  unsigned int _randomSeed = time(NULL);
};

#endif // CHIP8_CONFIG_H_
