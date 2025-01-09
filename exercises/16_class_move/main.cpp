#include "../exercise.h"
#include <utility> // for std::move

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]{0, 1}), cached(2), capacity(capacity) {}

    // 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr; // 源对象不再拥有资源
        other.cached = 0;
        other.capacity = 0;
    }

    // 实现移动赋值
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this == &other) {
            return *this; // 处理自我赋值
        }

        delete[] cache; // 释放已有资源

        // 移动资源
        cache = other.cache;
        cached = other.cached;
        capacity = other.capacity;

        other.cache = nullptr; // 源对象不再拥有资源
        other.cached = 0;
        other.capacity = 0;

        return *this;
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        if (i < cached) {
            return cache[i]; // 如果 i 已经在缓存中，直接返回
        }

        // 从已缓存的位置开始计算，直到计算到第 i 项
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        cached = i + 1; // 更新已缓存的最大索引
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
