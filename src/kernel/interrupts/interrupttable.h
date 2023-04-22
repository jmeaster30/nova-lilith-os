#pragma once

#include <stdint.h>

namespace Kernel {

  class __attribute__((__packed__)) InterruptDescriptor {
    public:
      InterruptDescriptor(){};
      InterruptDescriptor(void* isr, uint16_t selector, uint8_t flags);
    
    private:
      uint16_t isr_low = 0;
      uint16_t kernel_cs = 0;
      uint8_t reserved = 0;
      uint8_t attributes = 0;
      uint16_t isr_high = 0;
  };

  struct __attribute__((__packed__)) IDTDescriptor {
    uint16_t limit;
    uint32_t base;
  };

  class InterruptDescriptorTable {
    public:
      InterruptDescriptorTable(){}
      
      void Initialize();
    private:
      InterruptDescriptor __attribute__((aligned(0x10))) table[256];

      uint16_t size;

      IDTDescriptor idtDescriptor;
  };

}
