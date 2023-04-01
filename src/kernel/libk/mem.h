#pragma once

#include <stddef.h>

namespace LibK {
  // return -1 if a < b
  // return 1 if b < a
  // return 0 if a = b
  int compare(const void*, const void*, size_t);
  int copy(void*, const void*, size_t);
  int set(void*, unsigned char, size_t);
  size_t length(const char*);
}