#include "interrupttable.h"

#include <libk/io.h>

extern void* ISR0;
extern void* ISR1;

namespace Kernel {
  InterruptDescriptor::InterruptDescriptor(void* isr, uint16_t selector, uint8_t flags) {
    isr_low =    (uint32_t)isr & 0xFFFF;
    kernel_cs =  selector;
    attributes = flags;
    isr_high =   (uint32_t)isr >> 16;
    reserved =   0;
  }
  
  void InterruptDescriptorTable::Initialize() {
    for (int i = 0; i < 32; i++) {
      auto isr_addr = ((i * ((uint32_t)ISR1 - (uint32_t)ISR0)) + (uint32_t)ISR0);
      table[size++] = InterruptDescriptor((void*)isr_addr, (uint16_t) 0x08, 0x8E);
    }
    
    idtDescriptor.base = (uintptr_t)table;
    idtDescriptor.limit = (size * sizeof(InterruptDescriptor)) - 1;

    LibK::formatln("IDT TABLE ADDRESS:    %x", &table[0]);
    LibK::formatln("IDT DESCRIPTOR BASE:  %x", idtDescriptor.base);
    LibK::formatln("IDT DESCRIPTOR LIMIT: %i", idtDescriptor.limit);

    asm ("LIDT %[idtd]" : : [idtd] "m" (idtDescriptor));
    asm ("STI");
  }
}