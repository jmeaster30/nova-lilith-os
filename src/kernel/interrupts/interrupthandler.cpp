#include "interrupthandler.h"

#include <libk/io.h>

namespace Kernel {
  extern "C" void InterruptHandler(int interrupt) {
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    LibK::formatln("TEST");
    asm volatile ("cli; hlt");
  }
}