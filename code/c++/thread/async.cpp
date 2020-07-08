#include <future>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

string helloFunction(const string& s) { return "Hello C++11 from " + s + "."; }

class HelloFunctionObject {
 public:
  string operator()(const string& s) const {
    return "Hello C++11 from " + s + ".";
  }
};

int main() {
  cout << endl;

  // 带函数的future
  auto futureFunction = async(helloFunction, "function");

  // 带函数对象的future
  HelloFunctionObject helloFunctionObject;
  ca auto futureFunctionObject = async(helloFunctionObject, "function object");

  // 带匿名函数的future
  auto futureLambda =
      async([](const string& s) { return "Hello C++11 from " + s + "."; },
            "lambda function");

  cout << futureFunction.get() << "\n"
       << futureFunctionObject.get() << "\n"
       << futureLambda.get() << endl;

  cout << endl;
}