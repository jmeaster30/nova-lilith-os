#include "io.h"

#include <stdarg.h>

#include <terminal/terminal.h>

namespace LibK {
  void printchar(char c) {
    Kernel::Terminal::PutChar(c);
  }

  void print(const char* c) {
    Kernel::Terminal::Write(c);
  }

  void println(const char* c) {
    print(c);
    printchar('\n');
  }

  void print_int(int i) {
    int digitMask = 1000000000;
    int remainder = i;
    bool foundStart = false;

    if (remainder < 0) {
      printchar('-');
      remainder *= -1;
    }

    while (remainder > 0) {
      int value = (remainder / digitMask) % 10;
      if (!foundStart && value != 0) {
        foundStart = true;
      }

      if (foundStart) {
        printchar(value + 48);
        remainder %= digitMask;
      }
      
      digitMask /= 10;
    }
  }

  void print_bits(unsigned int i) {
    print("0b");
    int exp = 32;
    while (exp > 0) {
      printchar(((i >> exp) & 1) + 48);
      exp -= 1;
    }
  }

  void print_hex(unsigned int i) {
    print("0x");
    int shift = 28;
    while (shift >= 0) {
      int value = (i >> shift) & 0xF;
      if (value >= 0 && value < 10) {
        printchar(value + 48);
      } else if (value >= 10 && value < 16) {
        printchar(value + 55);
      } else {
        printchar('.');
      }
      shift -= 4;
    }
  }

  void format_internal(const char* c, va_list args) {
    auto current = c[0];
    int currentIndex = 0;
    bool foundPercent = false;

    while (current != '\0') {
      if (current == '%') {
        if (foundPercent) {
          printchar(current);
          foundPercent = false;
        } else {
          foundPercent = true;
        }
      } else if (foundPercent) {
        if (current == 's') {
          const char* str = va_arg(args, const char*);
          print(str);
        } else if (current == 'c') {
          char c = (char)va_arg(args, int);
          printchar(c);
        } else if (current == 'i') {
          int i = va_arg(args, int);
          print_int(i);
        } else if (current == 'b') {
          int i = va_arg(args, int);
          print_bits(i);
        } else if (current == 'x') {
          int i = va_arg(args, int);
          print_hex(i);
        }
        foundPercent = false;
      } else {
        printchar(current);
      }
      currentIndex += 1;
      current = c[currentIndex];
    }
  }

  void format(const char* c, ...) {
    if (c == nullptr) return;
    va_list parameters;
	  va_start(parameters, c);
    format_internal(c, parameters);
    va_end(parameters);
  }

  void formatln(const char* c, ...) {
    if (c == nullptr) return;
    va_list parameters;
	  va_start(parameters, c);
    format_internal(c, parameters);
    va_end(parameters);
    printchar('\n');
  }
}