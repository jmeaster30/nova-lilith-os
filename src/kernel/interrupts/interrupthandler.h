#pragma once

#include <stdint.h>

namespace Kernel {
  extern "C" void ExceptionHandler(int);
  extern "C" void InterruptHandler(int);
}
