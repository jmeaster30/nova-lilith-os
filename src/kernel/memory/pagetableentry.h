#pragma once

#include <stdint.h>

namespace Kernel {

class PageTableEntry {
  public:
    uint32_t GetAddress();
    bool GetPageAttributeTable();
    bool GetGlobal();
    bool GetDirty();
    bool GetAccessed();
    bool GetPageNotCached();
    bool GetPageWriteThrough();
    bool GetUserSupervisor();
    bool GetReadWrite();
    bool GetPresent();
    uint8_t GetAvailable();

    PageTableEntry(uint32_t data) : data(data) {}

  private:
    uint32_t data;
};

}