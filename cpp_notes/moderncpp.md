# 现代C++简介
现代C++(Modern C++)是相对于C++98/03而言，C++11后引入了很多特性

# C++11
## 核心语言功能特性
- auto 与 decltype 
- final 与 override
- 尾随返回类型
- 右值引用
- 移动构造函数与移动赋值运算符
- 有作用域枚举
- constexpr 与字面类型
- 列表初始化
- 委托与继承的构造函数
- 花括号或等号初始化器
- nullptr
- long long
- char16_t 与 char32_t
- 类型别名
- 变参数模板
- 推广的（非平凡）联合体
- 推广的 POD （平凡类型与标准布局类型）
- Unicode 字符串字面量
- 用户定义字面量
- 属性
- lambda 表达式
- noexcept 说明符与 noexcept 运算符
- alignof 与 alignas
- 多线程内存模型
- 线程局部存储 

## 库功能特性 
- type_traits：类型支持库
- chrono: 时间日期库
- initializer_list: 初始化列表  
- 容器：unordered_set, unordered_map, tuople, array, forward_list
- random: 伪随机 
- regex：正则表达式
- atomic：原子操作
- 线程支持： mutex，future，condition_variable>  

# C++14

## 新语言功能特性
- 变量模板
- 泛型 lambda
- lambda 初始化捕获
- new/delete 消除
- constexpr 函数上放松的限制
- 二进制字面量：如 `int b = 0b101010; // C++14`
- 数位分隔符: 如`long k = 1'234'567'890`
- 函数的返回类型推导：使用auto自动推导函数返回类型
- 带默认成员初始化器的聚合类

## 新库功能特性
- std::make_unique 
- std::integer_sequence: 编译期的整数序列
- std::exchange：值替换，对象必须能移动
- std::quoted： 引用字符串的处理
# C++17
## 新的语言特性
- 折叠表达式：用于变长模板的展开
- 类模板实参推导
- auto 占位的非类型模板形参
- 编译期的 constexpr if 语句
- inline 变量
- 结构化绑定
- if 和 switch 语句中的初始化器
- u8-char
- 简化的嵌套命名空间
- using 声明语句可以声明多个名称
- 将 noexcept 作为类型系统的一部分
- 新的求值顺序规则
- 强制的复制消除
- lambda 表达式捕获 *this
- constexpr 的 lambda 表达式
- 属性命名空间不必重复
- 新属性 [[fallthrough]] [[nodiscard]] 和 [[maybe_unused]]
- __has_include   

## 新的库特性 

- string_view: 只读的字符串视图，提升性能
- filesystem: 文件系统支持
- from_chars/to_chars: 字符和数字转换
- any： 保有任何可复制构造 (CopyConstructible) 类型的实例的对象
- optional： 可选值
- variant： 类型安全的联合体  
- 并行算法与执行策略：algorithm库中，增加并行化支持 
- 数学特殊函数cmath： 
 

# C++20

## 新的语言特性 
- 协程
- 模块
- 限定与概念 

## 新的库特性
新的头文件
- concepts: 模板的限制条件，友好的错误提示
- coroutine：协程 
- format： 格式化支持
- span: 对象的连续序列上的无所有权视图
- ranges: 允许通过指代元素范围的迭代器和哨位，在其元素上迭代的类型。 
- std::jthread: thread 自动合并和取消的实现版本 

```cpp
// conccept: 四种写法
//(1)
Integral auto Add(Integral auto a, Integral auto b) {
    return a + b;
}
//(2)
template<typename T> 
requires Integral<T>
T Add(T a, T b) {
    return a + b;
}
//(3)
template<typename T>
T Add(T a, T b) requires Integral<T> {
    return a + b;
}
//(4)
template<Integral T>
T Add(T a, T b) {
    return a + b;
}
 
```
```cpp
// range演示
#include <iostream>
#include <ranges>
#include <vector>

int main() {
  auto ints = std::views::iota(0, 10);
  auto even = [](int i) { return 0 == i % 2; };
  auto square = [](int i) { return i * i; };

	for(auto i: ints)
		std::cout << i << " ";
	std::cout << std::endl;

  for (int i : ints | std::views::filter(even) | std::views::transform(square))
    std::cout << i << ' ';
}
```

```cpp
#include <iostream>
#include <span>
#include <string_view>

void print(std::string_view const title,
           /* std::ranges::forward_range */ auto const& container) {
  std::cout << title << "[" << std::size(container) << "]{ ";
  for (auto const& elem : container) std::cout << elem << ", ";
  std::cout << "};\n";
}

void run_game(std::span<const int> span) {
  print("span: ", span);

  std::span<const int, 5> span_first = span.first<5>();
  print("span.first<5>(): ", span_first);

  std::span<const int, std::dynamic_extent> span_first_dynamic = span.first(4);
  print("span.first(4):   ", span_first_dynamic);
}

int main() {
  int a[8]{
      1, 2, 3, 4, 5, 6, 7, 8,
  };
  print("int  a", a);
  run_game(a);
}
```