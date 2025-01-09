#include "../exercise.h"

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    DynFibonacci(int capacity) : cache(new size_t[capacity]{0, 1}), cached(2), capacity(capacity) {}

    DynFibonacci(DynFibonacci const &) = delete;

    ~DynFibonacci() {
        delete[] cache;
    }

    size_t get(int i) {
        if (i < cached) {
            return cache[i];
        }
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1;
        return cache[i];
    }

    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const &fib_ = fib;  // 使用引用，避免复制构造
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
