#include "abort.h"

#include <libk/io.h>

namespace LibK {

  __attribute__((__noreturn__))
  void abort(void) {
    println("kernel: panic: abort()");
    asm volatile("hlt");

    while (1) {}
    __builtin_unreachable();
  }

}