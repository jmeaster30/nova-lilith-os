#include "descriptortable.h"

#include <libk/io.h>

using namespace LibK;

namespace Kernel {
  void GlobalDescriptorTable::Initialize() {
    // Using 32 bit Setup from https://wiki.osdev.org/GDT_Tutorial#Flat_.2F_Long_Mode_Setup
    size = 0;

    // Null descriptor
    table[size++] = SegmentDescriptor(); // everything is default initialized to zero (I think)

    formatln("SegmentDescriptor: %i", size - 1);
    format("\tBASE   %x", table[size - 1].GetBase());
    formatln("\tLIMIT  %x", table[size - 1].GetLimit());
    format("\tACCESS %x", table[size - 1].GetAccess());
    formatln("\tFLAGS  %x", table[size - 1].GetFlags());

    // Kernel Mode Code Segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    formatln("SegmentDescriptor: %i", size - 1);
    format("\tBASE   %x", table[size - 1].GetBase());
    formatln("\tLIMIT  %x", table[size - 1].GetLimit());
    format("\tACCESS %x", table[size - 1].GetAccess());
    formatln("\tFLAGS  %x", table[size - 1].GetFlags());

    // Kernel Mode Data Segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    formatln("SegmentDescriptor: %i", size - 1);
    format("\tBASE   %x", table[size - 1].GetBase());
    formatln("\tLIMIT  %x", table[size - 1].GetLimit());
    format("\tACCESS %x", table[size - 1].GetAccess());
    formatln("\tFLAGS  %x", table[size - 1].GetFlags());

    // User mode code segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    formatln("SegmentDescriptor: %i", size - 1);
    format("\tBASE   %x", table[size - 1].GetBase());
    formatln("\tLIMIT  %x", table[size - 1].GetLimit());
    format("\tACCESS %x", table[size - 1].GetAccess());
    formatln("\tFLAGS  %x", table[size - 1].GetFlags());

    // User mode data segment
    table[size++] = SegmentDescriptor(
        0,
        0xFFFFF,
        ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE,
        FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    formatln("SegmentDescriptor: %i", size - 1);
    format("\tBASE   %x", table[size - 1].GetBase());
    formatln("\tLIMIT  %x", table[size - 1].GetLimit());
    format("\tACCESS %x", table[size - 1].GetAccess());
    formatln("\tFLAGS  %x", table[size - 1].GetFlags());

    // TODO add Task State Segment

    formatln("GDT Table Size : %i", size);

    // load table into the cpu
    gdtDescriptor.size = (uint16_t)((size * sizeof(SegmentDescriptor)) - 1);
    gdtDescriptor.location = &table[0];
    asm ("LGDT %[gdtd]" : : [gdtd] "m" (gdtDescriptor));
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