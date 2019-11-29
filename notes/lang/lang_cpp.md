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

```c++
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

```c++
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
