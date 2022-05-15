
class Fibonacci {
public:
  uint64_t getNumber(uint64_t n) {
    uint64_t f[n + 2];
    uint64_t i;
    f[0] = 0;
    f[1] = 1;
    for (i = 2; i <= n; i++) {
      f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
  }
};