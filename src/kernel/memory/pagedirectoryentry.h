#pragma once

#include <stdint.h>

namespace Kernel {

class PageDirectoryEntry {
  public:
    uint32_t GetAddress();
    bool GetPageAttributeTable();
    bool GetGlobal();
    bool GetPageSize();
    bool GetDirty();
    bool GetAccessed();
    bool GetPageNotCached();
    bool GetPageWriteThrough();
    bool GetUserSupervisor();
    bool GetReadWrite();
    bool GetPresent();
    uint8_t GetAvailable();

    PageDirectoryEntry(uint32_t data) : data(data) {}
  
  private:
    uint32_t data = {};
};

}