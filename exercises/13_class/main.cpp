#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造器
    Fibonacci() : cache{0, 1}, cached(2) {}

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
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
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
