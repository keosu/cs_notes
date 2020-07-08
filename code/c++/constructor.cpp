// C++ 类的构造过程
// 编译器使用g++ 7.3 ，注意选项 -fno-elide-constructors
// 该选项说明：
// The C++ standard allows an implementation to omit creating a temporary that is only used to 
// initialize another object of the same type. Specifying this option disables that optimization, 
// and forces G++ to call the copy constructor in all cases.


// 无该选项时，一些过程被优化了，此时输出：
// -------------------------1-------------------------
// Constructor
// -------------------------2-------------------------
// Copy Constructor
// -------------------------3-------------------------
// Copy Constructor
// -------------------------4-------------------------
// Copy Assignment operator
// -------------------------5-------------------------
// Constructor
// -------------------------6-------------------------
// Move Constructor
// -------------------------7-------------------------
// Constructor
// -------------------------8-------------------------
// Constructor
// -------------------------9-------------------------
// Constructor
// Move Assignment operator

// 使能该选项，禁用优化，此时输出：
// -------------------------1-------------------------
// Constructor
// -------------------------2-------------------------
// Copy Constructor
// -------------------------3-------------------------
// Copy Constructor
// -------------------------4-------------------------
// Copy Assignment operator
// -------------------------5-------------------------
// Constructor
// Move Constructor
// -------------------------6-------------------------
// Move Constructor
// -------------------------7-------------------------
// Constructor
// Move Constructor
// Move Constructor
// -------------------------8-------------------------
// Constructor
// -------------------------9-------------------------
// Constructor
// Move Assignment operator

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
  cout << "-------------------------1-------------------------" << endl;
  A a(1);
  cout << "-------------------------2-------------------------" << endl;
  A b = a;
  cout << "-------------------------3-------------------------" << endl;
  A c(a);
  cout << "-------------------------4-------------------------" << endl;
  b = a;
  cout << "-------------------------5-------------------------" << endl;
  A d = A(1);
  cout << "-------------------------6-------------------------" << endl;
  A e = std::move(a);
  cout << "-------------------------7-------------------------" << endl;
  A f = GetA();
  cout << "-------------------------8-------------------------" << endl;
  A&& g = MoveA();
  cout << "-------------------------9-------------------------" << endl;
  d = A(1);
}