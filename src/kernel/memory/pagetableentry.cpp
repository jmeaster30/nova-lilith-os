#include "pagetableentry.h"

namespace Kernel {

uint32_t PageTableEntry::GetAddress() {
  return data & 0xFFFFF000;
}

bool PageTableEntry::GetGlobal() {
  return data & 256;
}

bool PageTableEntry::GetPageAttributeTable() {
  return data & 128;
}

bool PageTableEntry::GetDirty() {
  return data & 64;
}

bool PageTableEntry::GetAccessed() {
  return data & 32;
}

bool PageTableEntry::GetPageNotCached() {
  return data & 16;
}

bool PageTableEntry::GetPageWriteThrough() {
  return data & 8;
}

bool PageTableEntry::GetUserSupervisor() {
  return data & 4;
}

bool PageTableEntry::GetReadWrite() {
  return data & 2;
}

bool PageTableEntry::GetPresent() {
  return data & 1;
}

uint8_t PageTableEntry::GetAvailable() {
  return data >> 9;
}

}