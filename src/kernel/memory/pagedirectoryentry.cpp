#include "pagedirectoryentry.h"

namespace Kernel {

uint32_t PageDirectoryEntry::GetAddress() {
  if (GetPageSize()) {
    // bits 13 to 20 are bits 32 to 39 of the physical address but we are 32 bit so it doesn't make sense??
    return data & 0xFF400000;
  } else {
    return data & 0xFFFFF000;
  }
}

bool PageDirectoryEntry::GetPageAttributeTable() {
  if (GetPageSize()) {
    return data & 4096;
  } else {
    return false;
  }
}

bool PageDirectoryEntry::GetGlobal() {
  return data & 256;
}

bool PageDirectoryEntry::GetPageSize() {
  return data & 128;
}

bool PageDirectoryEntry::GetDirty() {
  return data & 64;
}

bool PageDirectoryEntry::GetAccessed() {
  return data & 32;
}

bool PageDirectoryEntry::GetPageNotCached() {
  return data & 16;
}

bool PageDirectoryEntry::GetPageWriteThrough() {
  return data & 8;
}

bool PageDirectoryEntry::GetUserSupervisor() {
  return data & 4;
}

bool PageDirectoryEntry::GetReadWrite() {
  return data & 2;
}

bool PageDirectoryEntry::GetPresent() {
  return data & 1;
}

uint8_t PageDirectoryEntry::GetAvailable() {
  return (data >> 6) & (GetPageSize() ? 56 : 61);
}
}