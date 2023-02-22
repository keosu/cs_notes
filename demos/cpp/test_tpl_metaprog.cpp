#include <iostream>
#include <utility>  // std::swap

template <int n>
class IntBubbleSortC {
  template <int i, int j>
  static inline void IntSwap(int* data) {  // 比较和交换两个相邻元素
    if (data[i] > data[j]) std::swap(data[i], data[j]);
  }
  template <int i, int j>
  static inline void IntBubbleSortLoop(int* data) {  // 一次冒泡
    IntSwap<j, j + 1>(data);
    constexpr int ii = j < i - 1 ? i : 0;
    constexpr int jj = j < i - 1 ? (j + 1) : 0;
    IntBubbleSortLoop<ii, jj>(data);
  }
  template <>
  static inline void IntBubbleSortLoop<0, 0>(int*) {}

 public:
  static inline void sort(int* data) {
    IntBubbleSortLoop<n - 1, 0>(data);
    IntBubbleSortC<n - 1>::sort(data);
  }
};
template <>
class IntBubbleSortC<0> {
 public:
  static inline void sort(int* data) {}
};

int main() {
  int data[] = {3, 4, 2, 1,7,9,8,0};
  const int len = sizeof(data)/sizeof(int);
  IntBubbleSortC<len>::sort(data);  
  for (size_t i = 0; i < len; i++) {
    std::cout << data[i] << " ";
  }

  return 0;
}