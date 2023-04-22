#pragma once

#include <stdint.h>

#define ACCESS_PRESENT 0b10000000

#define ACCESS_RING_1 0b00100000
#define ACCESS_RING_2 0b01000000
#define ACCESS_RING_3 0b01100000

#define ACCESS_CODE_DATA_SEGMENT 0b00010000

#define ACCESS_EXECUTABLE    0b00001000
#define ACCESS_DIRECTION_SET 0b00000100
#define ACCESS_READ_WRITE    0b00000010

#define FLAGS_PAGE_GRANULARITY 0b00001000
#define FLAGS_SIZE_SET         0b00000100
#define FLAGS_LONG_MODE        0b00000010

namespace Kernel {

  class __attribute__ ((__packed__)) SegmentDescriptor {
  public:
    SegmentDescriptor() {};
    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

    inline uint32_t GetBase() {
      return base1 | (base2 << 16) | (base3 << 24);
    };
    inline uint32_t GetLimit() {
      return limit | ((limitFlags & 0x0F) << 16);
    };
    inline uint8_t  GetAccess() {
      return access;
    };
    inline uint8_t  GetFlags() {
      return (limitFlags >> 4) & 0x0F;
    };

    // TODO System Segment Descriptor
    // TODO Long Mode System Segment Descriptor

  private:
    uint16_t limit = 0;
    uint16_t base1 = 0;
    uint8_t base2  = 0;
    uint8_t access = 0;
    uint8_t limitFlags = 0;
    uint8_t base3 = 0;
  };

  struct __attribute__ ((__packed__)) GDTDescriptor {
    uint16_t size;
    SegmentDescriptor* location;
  };

  class GlobalDescriptorTable {
    public:
      GlobalDescriptorTable(){}

      void Initialize();
    private:
      // GDT can be up to 65536 bytes in length with 8192 entries
      // Do we initialize space for all 8192 at one time?
      SegmentDescriptor table[256];

      // size of table
      uint16_t size;

      GDTDescriptor gdtDescriptor;
  };

}
