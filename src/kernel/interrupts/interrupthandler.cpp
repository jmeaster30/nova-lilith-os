#include "interrupthandler.h"

namespace Kernel {
  extern "C" void InterruptHandler(int interrupt) {
    asm volatile ("cli; hlt");
  }
}