#include <chrono>    // seconds
#include <future>    // promise, future
#include <iostream>  // cout, endl
#include <string>    // string
#include <thread>    // thread

using namespace std::chrono;
using namespace std;

void read(future<string> *future) {
  // future会一直阻塞，直到有值到来
  cout << future->get() << endl;
}

int main() {
  // promise 相当于生产者
  promise<string> promise;
  // future 相当于消费者, 右值构造
  future<string> future = promise.get_future();
  // 另一线程中通过future来读取promise的值
  thread thread(read, &future);
  // 让read等一会儿:)
  this_thread::sleep_for(seconds(1));
  //
  promise.set_value("hello future");
  // 等待线程执行完成
  thread.join();

  return 0;
}