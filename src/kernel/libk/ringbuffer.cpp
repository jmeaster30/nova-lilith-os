#include "ringbuffer.h"

namespace LibK {
  template<typename T, uint32_t bufferSize>
  bool RingBuffer<T, bufferSize>::IsEmpty() const {
    return first == last;
  }
  
  template<typename T, uint32_t bufferSize>
  bool RingBuffer<T, bufferSize>::IsFull() const {
    return first == next;
  }

  template<typename T, uint32_t bufferSize>
  uint32_t RingBuffer<T, bufferSize>::Size() const {
    if (first < last) {
      return next - first;
    }

    return (next + bufferSize) - first;
  }

  template<typename T, uint32_t bufferSize>
  bool RingBuffer<T, bufferSize>::Pop(T& result) {
    if (IsEmpty()) return false;

    result = buffer[first];
    first = (first + 1) % bufferSize;

    return true;
  }

  template<typename T, uint32_t bufferSize>
  bool RingBuffer<T, bufferSize>::Push(T value) {
    if(IsFull()) return false;

    buffer[next] = value;
    next = (next + 1) % bufferSize;
    last = (last + 1) % bufferSize;

    return true;
  }

}