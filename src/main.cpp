#include <filesystem>
#include <iostream>
#include <signal.h>

#include "chip8.hpp"
#include "file_rom.hpp"

#include "terminal_frontend.hpp"
#include "terminal_input.hpp"

static constexpr char *ROM_DIRECTORY = "files/roms/";

static void handleKeyboardInterrupt(int s) {
  term_chip8::teardownDisplay();
  exit(0);
}

static void setupKeyboardInterruptHandler() {
  // Handle keyboard interrupt
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler = handleKeyboardInterrupt;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);
}

static void emulateChip8() {

  std::unique_ptr<IInput> input = std::make_unique<TerminalInput>();
  chip8::Chip8Interface interface(std::move(input), term_chip8::updateDisplay,
                                  [](chip8::Chip8 *) {});
  chip8::Chip8 chip8 = chip8::Chip8(std::move(interface));
  chip8.init();

  auto res =
      chip8.loadRom(std::make_unique<chip8::FileROM>("files/roms/guess.ch8"));
  if (res) {
    chip8.run();
  } else {
    std::cout << "couldn't load the rom ):\n";
  }
}

int main() {
  term_chip8::setupDisplay();
  // display options, let user choose ROM
  setupKeyboardInterruptHandler();
  emulateChip8();
  term_chip8::teardownDisplay();
}
