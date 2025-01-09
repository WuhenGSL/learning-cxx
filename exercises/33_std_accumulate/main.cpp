#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};

    // 使用 std::accumulate 计算总元素数
    int size = std::accumulate(shape, shape + 4, 1, std::multiplies<int>()) * sizeof(DataType);

    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
