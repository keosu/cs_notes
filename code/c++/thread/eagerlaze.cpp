#include <chrono>
#include <future>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
  cout << endl;

  auto begin = system_clock::now();

  auto asyncLazy = async(launch::deferred, [] { return system_clock::now(); });

  auto asyncEager = async(launch::async, [] { return system_clock::now(); });

  this_thread::sleep_for(seconds(1));

  auto lazyStart = asyncLazy.get() - begin;
  auto eagerStart = asyncEager.get() - begin;

  auto lazyDuration = duration<double>(lazyStart).count();
  auto eagerDuration = duration<double>(eagerStart).count();

  cout << "asyncLazy evaluated after : " << lazyDuration << " seconds." << endl;
  cout << "asyncEager evaluated after: " << eagerDuration << " seconds."
       << endl;

  cout << endl;
}