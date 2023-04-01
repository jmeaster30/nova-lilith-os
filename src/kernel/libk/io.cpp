#include "io.h"

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
    Kernel::Terminal::PutChar('\n');
  }

  void format(const char* c, ...) {
    print(c);
  }

  void formatln(const char* c, ...) {
    println(c);
  }
}