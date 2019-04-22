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
### 继承
  继承属性：public protected private  
  多继承
  虚继承

- 重载 ： 实现编译时多态
- 虚函数 ： 实现运行时多态

纯虚函数，抽象类
虚继承
```
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
  pa->show();pb->show();pc->show();
  pa->show2();pb->show2();pc->show2();

  return 0;
}
```

## 5. 输入输出字符串

## 6. C++11

## 7. 其他
