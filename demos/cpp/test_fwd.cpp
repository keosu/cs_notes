#include <iostream>


class Runner {
  template <typename... Args>
  void operator()(Args&&... args) {
    set(0, std::forward<Args>(args)...);
    start();
  }

  template <typename T, typename... Args>
  void set(int argno, T&& arg, Args&&... args) {
    set(argno, std::forward<T>(arg));
    set(++argno, std::forward<Args>(args)...);
  }

  template <typename ArgType>
  void set(int index, ArgType&& arg) {
    // ...
  }
};