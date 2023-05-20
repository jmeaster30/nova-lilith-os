#pragma once

#include <stdint.h>

namespace Kernel {
  class Keyboard {
  public:
    enum ScanCode {
      SET_1, SET_2, SET_3
    };

    enum ModKeyMasks {
      L_CONTROL = 1,
      L_SUPER = 2,
      L_ALT = 4,
      L_SHIFT = 8,
      CAPS_LOCK = 16,
      R_CONTROL = 32,
      R_SUPER = 64,
      R_ALT = 128,
      R_SHIFT = 256,
      SCROLL_LOCK = 512,
      NUM_LOCK = 1024,
    };

    static uint8_t getscancode();
    static uint8_t getkey();
    static uint8_t getkey(uint16_t);
    static uint8_t getkey(uint8_t, uint16_t);
  private:
    static const uint8_t port = 0x60;
  };
}
