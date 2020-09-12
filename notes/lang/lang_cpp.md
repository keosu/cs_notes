# 极简C++

## 1. 简介

## 2. 语法基础

## 3. 函数

### 函数传递参数-引用？指针？
- 传递数据很小，如内置类型或小结构，按值传递
- 传递数组，使用指针，无需修改加const
- 传递结构，使用指针或引用，无需修改加const
- 传递类对象，使用引用，无需修改加const

## 4. 类
  面向对象基本特征：封装、继承、多态

### 类的大小 sizeof(AClass)  
1. 为类的非静态成员数据的类型大小之和．
2. 有编译器额外加入的成员变量的大小，用来支持语言的某些特性（如：指向虚函数的指针、虚继承、多重继承）．
3. 为了优化存取效率，进行的边缘调整．
4. 与类中的构造函数，析构函数以及其他的成员函数无关．
5. 私有继承，会去继承之前的私有成员变量么？ 会...在内存中仍然分配相应的空间，只是在子类中是不可见的！
6. 在做多层次的继承类大小时某个子类的类大小总是等于父类的大小加上子类中数据成员和是否有虚函数，是否是虚继承等因素来决定。

### 继承

  继承属性：public protected private  
  下面列出三种不同的继承方式的基类特性和派生类特性：  
  
继承方式\基类状态 | public     |  protected   |    private  
---------------|------------|--------------|---  
public         | public     |  protected   |    不可见  
protected      | protected  |  protected   |    不可见   
private        | private    |  private     |    不可见   

  多继承
  虚继承： 解决多继承的二义问题

- 重载 ： 实现编译时多态
- 虚函数 ： 实现运行时多态

纯虚函数: virtual 返回值类型 函数名 (函数参数) = 0;  
抽象类: 包含纯虚函数的类称为抽象类(Abstract Class),它无法实例化，也就是无法创建对象。  

```cpp
#include <iostream>
using namespace std;

class A {
 private:
 public:
  A() { cout << "A construct" << endl; }
  ~A() { cout << "A deconstruct " << endl; }

  virtual void show() { cout << "A show()" << endl; }
  void show2() { cout << "A show2()" << endl; }
};

class B : public A {
public:
  void show() { cout << "B show()" << endl; }
  void show2() { cout << "B show2()" << endl; }
};
;
class C : public A {

public:
	C(){ cout << " construct" << endl;}
  void show() { cout << "C show()" << endl; }
  void show2() { cout << "C show2()" << endl; }
  void show(string msg) { cout << "C show() msg " << endl; }
};

int main(int argc, char **argv)
{
  A a, *pa, *pb, *pc;
  B b;
  C c;
  pa = &a;pb = &b;pc = &c;

  cout << "A size()" << sizeof(A) << endl;
  cout << " B size()" << sizeof(B) << endl;
  cout << "C size()" << sizeof(C) << endl;

  a.show();b.show();c.show();
  // pb,pc 虽是A的指针，但它只想A的子类，show是虚函数，会执行B，C的实现
  pa->show();pb->show();pc->show();
  pa->show2();pb->show2();pc->show2();

  return 0;
}
```

## 5. 输入输出字符串

## 6. C++11

### 智能指针

```cpp
std::shared_ptr<int> sp(new int[10], std::default_delete<int[]>());
 
// 也可以使用一下的lambda表达式来自定义删除函数 
std::shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; });
 
// 实际上，除非需要共享目标，否则unique_ptr更适合使用数组： 
std::unique_ptr<int[]> up(new int[10]); // this will correctly call delete[]
 
//上面代码可以正确的分配空间，但是空间内的值都没有初始化。如果需要默认初始化为0，可以使用下面的代码： 
std::unique_ptr<int[]> up(new int[10]()); // this will correctly call delete[]  初始化为0

//成员函数
// relese() 获取并释放
// reset() 替换
// get() 获取
```

## 7. 其他

## code snippet

### lambda
```cpp
class A {
  int i_ = 0;

  void func(int x, int y) {
    // auto x1 = []{return i_; };  //error,没有捕获外部变量
    auto x2 = [=] { return i_ + x + y; };
    auto x3 = [&] { return i_ + x + y; };
    auto x4 = [this] { return i_; };
    // auto x5 = [this]{return i_ + x + y; };  //error,没有捕获x和y
    auto x6 = [this, x, y] { return i_ + x + y; };
    auto x7 = [this] { return i_++; };
  }
};
```

### decltype

```cpp

class Foo{};

int& func_int_r(void);    //左值（lvalue，可简单理解为可寻址值）
int&& func_int_rr(void);  //x值（xvalue，右值引用本身是一个xvalue）
int func_int(void);       //纯右值（pvalue）

const int& func_cint_r(void);         //左值
const int&& func_cint_rr(void);       //x值
const int func_cint(void);            //纯右值

const Foo func_cfoo(void);  //纯右值

int main(void)
{
	int x = 0;

	decltype(func_int_r()) a1 = x;    //a1 -> int&
	decltype(func_int_rr()) b1 = 0;   //b1 -> int&&
	decltype(func_int()) c1 = 0;      //c1 -> int

	decltype(func_cint_r()) a2 = x;    //a2 -> const int&
	decltype(func_cint_rr()) b2 = 0;   //b2 -> const int&&
	decltype(func_cint()) c2 = 0;      //c2 -> int

	decltype(func_cfoo()) ff = Foo();  //ff -> Foo

	system("pause");
	return 0;
}
```
###  初始化列表
```cpp
int i_arr[3] = {1, 2, 3};  //普通数组

struct A {
  int x;
  struct B {
    int i;
    int j;
  } b;
} a = {1, {2, 3}};  // POD类型

class FooVector {
  std::vector<int> content_;

 public:
  FooVector(std::initializer_list<int> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
      content_.push_back(*it);
    }
  }
};

class FooMap {
  std::map<int, int> content_;
  using pair_t = std::map<int, int>::value_type;

 public:
  FooMap(std::initializer_list<pair_t> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
      content_.insert(*it);
    }
  }
};

int main(void) {
  FooVector foo1 = {1, 2, 3, 4, 5};
  FooMap foo2 = {{1, 2}, {3, 4}, {5, 6}};

  return 0;
}
```
