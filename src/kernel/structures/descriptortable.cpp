#include "descriptortable.h"

#include <libk/io.h>

using namespace LibK;

namespace Kernel {
  void GlobalDescriptorTable::Initialize() {
    LibK::println("Initializing Global Descriptor Table...");
    // Using 32 bit Setup from https://wiki.osdev.org/GDT_Tutorial#Flat_.2F_Long_Mode_Setup
    size = 0;

    // Null descriptor
    table[size++] = SegmentDescriptor(0, 0, 0, 0);

    // Kernel Mode Code Segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // Kernel Mode Data Segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // User mode code segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // User mode data segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);
        
    // TODO add Task State Segment

    //formatln("GDT Table Size : %i", size);

    // load table into the cpu
    gdtDescriptor.size = (uint16_t)((size * sizeof(SegmentDescriptor)) - 1);
    gdtDescriptor.location = &table[0];
    asm ("LGDT %[gdtd]" : : [gdtd] "m" (gdtDescriptor));
    asm volatile(
      "ljmp $0x8, $.1;"
      ".1:"
      "mov $0x10, %ax;"
      "mov %ax, %ds;"
      "mov %ax, %es;"
      "mov %ax, %ss;"
    );
  }

  SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    this->base1 = base & 0xFFFF;
    this->base2 = (base >> 16) & 0xFF;
    this->base3 = (base >> 24) & 0xFF;
    if (limit > 0xFFFFF) {
      println("SegmentDescriptor cannot encode limit over 0xFFFFF");
    }
    this->limit = limit & 0xFFFF;
    this->limitFlags = (limit >> 16) & 0x0F;
    this->access = access;
    this->limitFlags |= ((flags & 0xF) << 4);
  }
}