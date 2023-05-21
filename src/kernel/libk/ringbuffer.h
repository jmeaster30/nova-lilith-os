#pragma once

#include <stdint.h>

namespace LibK {
  template<typename T, uint32_t bufferSize = 64>
  class RingBuffer {
    public:
      RingBuffer() {};

      bool IsEmpty() const;
      bool IsFull() const;
      uint32_t Size() const;

      bool Pop(T&);
      bool Push(T);

    private:
      T buffer[bufferSize];
      uint32_t first = 0;
      uint32_t last = 0;
      uint32_t next = 0; // This can probably be removed tbh
  };
}

