#include <functional>
#include <iostream>

using namespace std;

#include <functional>
#include <iostream>

void f(int& n1, int& n2, const int& n3) {
  cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  ++n1;  // increments the copy of n1 stored in the function object
  ++n2;  // increments the main()'s n2
         // ++n3; // compile error
}

int abc() {
  int n1 = 1, n2 = 2, n3 = 3;
  function<void()> bound_f = bind(f, n1, ref(n2), cref(n3));
  n1 = 10;
  n2 = 11;
  n3 = 12;
  cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  bound_f();
  cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  return 0;
}

int main(int argc, char** argv) {
  auto func = [=](int& n) -> int {
    cout << "N: " << n << endl;
    n++;
    return n;
  };

  int x = 1;
  cout << "ret: " << func(x) << endl;
  cout << "X: " << x << endl;
  

  return 0;
}