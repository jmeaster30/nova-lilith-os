#include "interrupttable.h"

#include <libk/io.h>

namespace Kernel {
  InterruptDescriptor::InterruptDescriptor(void* isr, uint16_t selector, uint8_t flags) {
    isr_low =    (uint32_t)isr & 0xFFFF;
    kernel_cs =  selector; // Kernel code segment. Probably want to have a better way to reference this specific descriptor table
    attributes = flags;
    isr_high =   (uint32_t)isr >> 16;
    reserved =   0;
  }
  
  void InterruptDescriptorTable::Initialize() {
    ISR(0);
    ISR(1);
    ISR(2);
    ISR(3);
    ISR(4);
    ISR(5);
    ISR(6);
    ISR(7);
    ISR(8);
    ISR(9);
    ISR(10);
    ISR(11);
    ISR(12);
    ISR(13);
    ISR(14);
    ISR(15);
    ISR(16);
    ISR(17);
    ISR(18);
    ISR(19);
    ISR(20);
    ISR(21);
    ISR(22);
    ISR(23);
    ISR(24);
    ISR(25);
    ISR(26);
    ISR(27);
    ISR(28);
    ISR(29);
    ISR(30);
    ISR(31);
    
    idtDescriptor.base = (uintptr_t)table;
    idtDescriptor.limit = (size * sizeof(InterruptDescriptor)) - 1;

    LibK::formatln("IDT TABLE ADDRESS:    %x", &table[0]);
    LibK::formatln("IDT DESCRIPTOR BASE:  %x", idtDescriptor.base);
    LibK::formatln("IDT DESCRIPTOR LIMIT: %i", idtDescriptor.limit);

    asm ("LIDT %[idtd]" : : [idtd] "m" (idtDescriptor));
    asm ("STI");
  }
}