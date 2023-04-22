#include "pic.h"

#include <libk/asm.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)

#define PIC_EOI 0x20
#define PIC_READ_IRR 0x0A
#define PIC_READ_ISR 0x0B

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SECONDARY	0x08		/* Buffered mode/secondary */
#define ICW4_BUF_PRIMARY	0x0C		/* Buffered mode/primary */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */



namespace Kernel {
  namespace PIC {
    void sendeoi(unsigned char interrupt) {
      if (interrupt >= 8)
        LibK::outb(PIC2_COMMAND, PIC_EOI);
      LibK::outb(PIC1_COMMAND, PIC_EOI); 
    }

    void remap(int offset1, int offset2) {
      unsigned char a1 = LibK::inb(PIC1_DATA);
      unsigned char a2 = LibK::inb(PIC2_DATA);

      LibK::outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
      LibK::iowait();
      LibK::outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
      LibK::iowait();
      LibK::outb(PIC1_DATA, offset1);
      LibK::iowait();
      LibK::outb(PIC2_DATA, offset2);
      LibK::iowait();
      LibK::outb(PIC1_DATA, 4);
      LibK::iowait();
      LibK::outb(PIC2_DATA, 2);
      LibK::iowait();
    
      LibK::outb(PIC1_DATA, ICW4_8086);
      LibK::iowait();
      LibK::outb(PIC2_DATA, ICW4_8086);
      LibK::iowait();
    
      LibK::outb(PIC1_DATA, a1);
      LibK::outb(PIC2_DATA, a2);
    }

    void setmask(unsigned char interrupt) {
      uint16_t port;
      uint8_t value;
  
      if(interrupt < 8) {
          port = PIC1_DATA;
      } else {
          port = PIC2_DATA;
          interrupt -= 8;
      }
      value = LibK::inb(port) | (1 << interrupt);
      LibK::outb(port, value);  
    }

    void clearmask(unsigned char interrupt) {
      uint16_t port;
      uint8_t value;
  
      if(interrupt < 8) {
          port = PIC1_DATA;
      } else {
          port = PIC2_DATA;
          interrupt -= 8;
      }
      value = LibK::inb(port) & ~(1 << interrupt);
      LibK::outb(port, value);
    }

    uint16_t getirq(int ocw3) {
      LibK::outb(PIC1_COMMAND, ocw3);
      LibK::outb(PIC2_COMMAND, ocw3);
      return (LibK::inb(PIC2_COMMAND) << 8) | LibK::inb(PIC1_COMMAND);
    }

    uint16_t getirr() {
      return getirq(PIC_READ_IRR);
    }

    uint16_t getisr() {
      return getirq(PIC_READ_ISR);
    }
  }
}
