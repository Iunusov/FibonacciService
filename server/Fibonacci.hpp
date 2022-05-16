#pragma once

class Fibonacci {
public:
  uint64_t getNumber(uint64_t n) {
    uint64_t a = 0;
    uint64_t b = 1;
    while (n-- > 1) {
      uint64_t t = a;
      a = b;
      b += t;
    }
    return b;
  }
};