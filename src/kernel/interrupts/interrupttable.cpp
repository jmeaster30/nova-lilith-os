#include "interrupttable.h"

#include <libk/io.h>
#include <libk/asm.h>
#include <interrupts/pic.h>

extern void* isr_stub_table[];

namespace Kernel {
  InterruptDescriptor::InterruptDescriptor(void* isr, uint16_t selector, uint8_t flags) {
    isr_low =    (uint32_t)isr & 0xFFFF;
    kernel_cs =  selector;
    attributes = flags;
    isr_high =   (uint32_t)isr >> 16;
    reserved =   0;
  }
  
  void InterruptDescriptorTable::Initialize() {
    LibK::println("Initializing Interrupt Table...");

    PIC::remap(0x20, 0x28);
    PIC::setmask(0);

    size = 0;
    for (int i = 0; i < 32; i++) {
      if (i < 18) {
        LibK::formatln("[%i] %x", i, isr_stub_table[i]);
      }
      table[size++] = InterruptDescriptor((void*)isr_stub_table[i], (uint16_t) 0x08, 0x8E);
    }
    
    idtDescriptor.base = (uintptr_t)table;
    idtDescriptor.limit = (size * sizeof(InterruptDescriptor)) - 1;

    LibK::formatln("IDT TABLE ADDRESS:    %x", table);
    LibK::formatln("IDT DESCRIPTOR BASE:  %x", idtDescriptor.base);
    LibK::formatln("IDT DESCRIPTOR LIMIT: %i", idtDescriptor.limit);

    asm volatile ("LIDT %[idtd]" : : [idtd] "m" (idtDescriptor));
  }
}