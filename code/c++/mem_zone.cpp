// 1. 内存栈区： 存放局部变量；
// 2. 内存堆区： 存放new或者malloc出来的对象；
// 3. 常数区： 存放全局常量；
// 4. 静态区： 存放全局变量或者静态变量；
// 5. 代码区：二进制代码。
#include <iostream>

using namespace std;
 

int ga = 5;
double gb = 4.5;
const int gca = 45;
const float gcb = 1.1;
const string s="abcd";
static int gsa = 123;
char gbuf[10] = {1};
char* gp;

int main(int argc, char** argv) {
  int la = 3;
  float lb = 3.4;
  const int ca = 123;
  static int sa = 5;
  static const int sca = 2;
  char lbuf[10]{1};
  char* lp;

  lp = new char[10];

  gp = new char[10];

  cout << "la addr: " << &la << endl;
  cout << "lb addr: " << &lb << endl;
  cout << "lbuf addr: " << static_cast<void*>(lbuf) << endl;

  cout << "ga addr: " << &ga << endl;
  cout << "gb addr: " << &gb << endl;
  cout << "gbuf addr: " << static_cast<void*>(gbuf) << endl;

  cout << "\n============ memory with new ===== " << endl;
  cout << "lp point at: " << static_cast<void*>(lp) << endl;
  cout << "gp point at: " << static_cast<void*>(gp) << endl;

  cout << "\n============ memory with static/const ===== " << endl;
  cout << "ca addr: " << &ca << endl;
  cout << "sa addr: " << &sa << endl;
  cout << "gca addr: " << &gca << endl;
  cout << "gsa addr: " << &gsa << endl;
  cout << "gcb addr: " << &gcb << endl;
  cout << "sca addr: " << &sca << endl;
  cout << "gstr addr: " << static_cast<const void*>(&s) << endl;

  return 0;
}