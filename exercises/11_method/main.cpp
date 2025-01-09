#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        if (i < cached) {
            return cache[i];  // 如果 i 已经在缓存中，直接返回缓存值
        }

        // 从已缓存的位置开始计算，直到计算到第 i 项
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        cached = i + 1;  // 更新已缓存的最大索引
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib = {{0, 1}, 2};  // 初始化前两个斐波那契数，并将 cached 设为 2
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
