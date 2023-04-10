#include "descriptortable.h"

#include <libk/io.h>

using namespace LibK;

namespace Kernel {
  void GlobalDescriptorTable::Initialize() {
    // Using 32 bit Setup from https://wiki.osdev.org/GDT_Tutorial#Flat_.2F_Long_Mode_Setup
    size = 0;

    // Null descriptor
    table[size++] = SegmentDescriptor::Create(); // everything is default initialized to zero (I think)
    
    // Kernel Mode Code Segment
    table[size++] = SegmentDescriptor::Create()
      .Base(0)
      .Limit(0xFFFFF)
      .Access(ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE)
      .Flags(FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // Kernel Mode Data Segment
    table[size++] = SegmentDescriptor::Create()
      .Base(0)
      .Limit(0xFFFFF)
      .Access(ACCESS_PRESENT | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE)
      .Flags(FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // User mode code segment
    table[size++] = SegmentDescriptor::Create()
      .Base(0)
      .Limit(0xFFFFF)
      .Access(ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_EXECUTABLE | ACCESS_READ_WRITE)
      .Flags(FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // User mode data segment
    table[size++] = SegmentDescriptor::Create()
      .Base(0)
      .Limit(0xFFFFF)
      .Access(ACCESS_PRESENT | ACCESS_RING_3 | ACCESS_CODE_DATA_SEGMENT | ACCESS_READ_WRITE)
      .Flags(FLAGS_PAGE_GRANULARITY | FLAGS_SIZE_SET);

    // TODO add Task State Segment

    formatln("GDT Table Size : %i", size);

    // load table into the cpu
    gdtDescriptor.size = (uint16_t)((size * sizeof(SegmentDescriptor)) - 1);
    gdtDescriptor.location = &table[0];
    asm ("LGDT %[gdtd]" : : [gdtd] "m" (gdtDescriptor));
  }

  SegmentDescriptor SegmentDescriptor::Limit(uint32_t limit) {
    if (limit > 0xFFFFF) {
      println("SegmentDescriptor cannot encode limit over 0xFFFFF");
    }

    this->limit = limit & 0xFFFF;
    this->limitFlags = (limit >> 16) & 0x0F;
    return *this;
  }

  SegmentDescriptor SegmentDescriptor::Base(uint32_t base) {
    this->base1 = base & 0xFFFF;
    this->base2 = (base >> 16) & 0xFF;
    this->base3 = (base >> 24) & 0xFF;
    return *this;
  }

  SegmentDescriptor SegmentDescriptor::Access(uint8_t access) {
    this->access = access;
    return *this;
  }

  SegmentDescriptor SegmentDescriptor::Flags(uint8_t flags) {
    this->limitFlags |= ((flags & 0xF) << 4);
    return *this;
  }
}