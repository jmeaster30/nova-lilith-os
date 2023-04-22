#pragma once

#include <stdint.h>

namespace Kernel {
  namespace PIC {
    void sendeoi(unsigned char);
    void remap(int offset1, int offset2);
    void setmask(unsigned char);
    void clearmask(unsigned char);
    uint16_t getirq(int);
    uint16_t getirr();
    uint16_t getisr();
  }
}