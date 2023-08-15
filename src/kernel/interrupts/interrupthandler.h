#pragma once

#include <stdint.h>

namespace Kernel {
  // TODO this should probably be somewhere else
  struct Registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
  };

  extern "C" void ExceptionHandler(struct Registers*);
  extern "C" void InterruptHandler(struct Registers*);
}
