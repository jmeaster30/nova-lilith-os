#pragma once

#include <stdint.h>

extern void* ISR0;
extern void* ISR1;
extern void* ISR2;
extern void* ISR3;
extern void* ISR4;
extern void* ISR5;
extern void* ISR6;
extern void* ISR7;
extern void* ISR8;
extern void* ISR9;
extern void* ISR10;
extern void* ISR11;
extern void* ISR12;
extern void* ISR13;
extern void* ISR14;
extern void* ISR15;
extern void* ISR16;
extern void* ISR17;
extern void* ISR18;
extern void* ISR19;
extern void* ISR20;
extern void* ISR21;
extern void* ISR22;
extern void* ISR23;
extern void* ISR24;
extern void* ISR25;
extern void* ISR26;
extern void* ISR27;
extern void* ISR28;
extern void* ISR29;
extern void* ISR30;
extern void* ISR31;

#define ISR(num) table[size++] = InterruptDescriptor(ISR##num, (uint16_t) 0x08, 0x8E);

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
