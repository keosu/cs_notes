
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <strstream>
#include <vector>
#include <numeric>

using namespace std;

struct Logits {
  Logits(int batch = 0) {
    start_logits.resize(batch * 128);
    end_logits.resize(batch * 128);
    start_idx.resize(batch * 128);
    end_idx.resize(batch * 128);
    for (auto i = 0; i < batch; i++) {
      std::iota(start_idx.begin() + 128 * i, start_idx.begin() + 128 * (i + 1), 0);
      std::iota(end_idx.begin() + 128 * i, end_idx.begin() + 128 * (i + 1), 0);
    }
  }
  std::vector<float> start_logits;
  std::vector<float> end_logits;
  std::vector<uint8_t> start_idx;
  std::vector<uint8_t> end_idx;
};
struct Logits2 { 
  float x[128];
  float y[128];
  uint8_t a[128];
  uint8_t b[128]; 
};


#include<iostream>  
#include <typeinfo>  
using namespace std;  

class Class1{};
class Class2:public Class1{};
void fn0();
int fn1(int n);

void test() {
    
}
void type_test(void)  
{  
    int a = 10;
    int* b = &a;
    float c;
    double d;

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(Class1).name() << endl;
    cout << typeid(Class2).name() << endl;
    cout << typeid(fn0).name() << endl;
    cout << typeid(fn1).name() << endl;
    cout << typeid(typeid(a).name()).name() << endl;
    // system("pause");
}  

int main(int argc, char** argv) {
  
  cout << "ispod:" << std::is_pod<Logits2>() << endl;
  cout << "ispod:" << std::is_trivial<Logits2>() << endl;
  cout << "ispod:" << std::is_trivially_copyable<Logits2>() << endl; 
  return 0;
}