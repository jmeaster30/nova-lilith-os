#pragma once

#include <stdint.h>

namespace LibK {
  static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port) );
    return result;
  }

  static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) );
  } 

  static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile ( "inl %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
  }

  static inline void outl(uint16_t port, uint32_t val) {
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
  }

  static inline void iowait() {
    asm volatile ( "jmp 1f\n\t 1:jmp 2f\n\t 2:" );
  }

  static inline void deactivate_interrupts() {
    asm volatile ("CLI");
  }

  static inline void activate_interrupts() {
    asm volatile ("STI");
  }
}