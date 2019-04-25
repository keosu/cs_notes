#include <iostream>
using namespace std;

class A {
 public:
  int x;
  A(int x) : x(x) { cout << "Constructor" << endl; }
  A(A& a) : x(a.x) { cout << "Copy Constructor" << endl; }
  A& operator=(A& a) {
    x = a.x;
    cout << "Copy Assignment operator" << endl;
    return *this;
  }
  A(A&& a) : x(a.x) { cout << "Move Constructor" << endl; }
  A& operator=(A&& a) {
    x = a.x;
    cout << "Move Assignment operator" << endl;
    return *this;
  }
};

A GetA() { return A(1); }

A&& MoveA() { return A(1); }

int main() {
  cout << "[1]  ";
  A a(1);
  cout << "[2]  ";
  A b = a;
  cout << "[3]  ";
  A c(a);
  cout << "[4]  ";
  b = a;
  cout << "[5]  ";
  A d = A(1);
  cout << "[6]  ";
  A e = std::move(a);
  cout << "[7]  ";
  A f = GetA();
  cout << "[8]  ";
  A&& g = MoveA();
  cout << "[9]  ";
  d = A(1);
}

// [1]  Constructor
// [2]  Copy Constructor
// [3]  Copy Constructor
// [4]  Copy Assignment operator
// [5]  Constructor
// [6]  Move Constructor
// [7]  Constructor
// [8]  Constructor
// [9]  Constructor
// Move Assignment operator

// 第1行毋庸置疑，调用构造函数。
// 第2行创建新对象b，使用a初始化b，因此调用拷贝构造函数。
// 第3行创建新对象c，使用a初始化c，因此调用拷贝构造函数。
// 第4行使用a的值更新对象b，因为不需要创建新对象，所以调用拷贝赋值运算符。
// 第5行创建新对象d，使用临时对象A(1)初始化d，由于临时对象是一个右值，所以调用移动构造函数。
// 第6行创建新对象e，使用a的值初始化e，但调用std::move(a)将左值a转化为右值，所以调用移动构造函数。
// 第7行创建新对象f，使用GetA()函数返回的临时对象初始化f，由于临时对象是右值，所以调用移动构造函数。值得注意的是，这里调用了两次移动构造函数。第一次是GetA()返回前，A(1)移动构造了一个临时对象。第二次是临时对象移动构造f。
// 第8行没有创建新对象，也不更新任何对象，只是将MoveA()的返回值绑定到右值引用g。因此不调用构造函数，也不调用赋值运算符。
// 第9行使用临时对象A(1)更新d，因为不需要创建新对象，所以调用移动赋值运算符。
