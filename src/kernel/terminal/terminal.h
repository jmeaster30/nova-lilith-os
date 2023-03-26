#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace Terminal {

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
    Terminal();

    void SetTextColor(VgaColor color);
    void SetBackgroundColor(VgaColor color);

    void PutChar(char c);
    void PutCharAt(char c, size_t x, size_t y);
    void Write(const char* data);
    void Write(const char* data, size_t size);
  
  private:
    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;

    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    VgaColor current_text_color;
    VgaColor current_background_color;
    uint16_t* terminal_buffer;

    
  };

}
