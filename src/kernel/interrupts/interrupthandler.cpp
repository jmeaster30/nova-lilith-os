#include "interrupthandler.h"

#include <terminal/terminal.h>
#include <interrupts/pic.h>

namespace Kernel {
  extern "C" void InterruptHandler(int interrupt) {
    switch (interrupt) {
      case 1: {
        Terminal::PutChar('@');
      }
    }
    PIC::sendeoi(interrupt);
  }
}