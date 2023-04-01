#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace Kernel {

  enum class VgaColor {
    Black = 0,
    Blue = 1, 
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGrey = 7,
    DarkGrey = 8,
    LightBlue = 9,
    LightGreen = 10, 
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    LightBrown = 14,
    White = 15,
  };

  class Terminal {
  public:
    static void Initialize();
    static void SetTextColor(VgaColor color);
    static void SetBackgroundColor(VgaColor color);

    static void PutChar(char c);
    static void PutCharAt(char c, size_t x, size_t y);
    static void Write(const char* data);
    static void Write(const char* data, size_t size);
  };
}
