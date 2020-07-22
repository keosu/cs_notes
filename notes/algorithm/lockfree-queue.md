# lockfree-queue C++ 无锁队列

C++标准库中的 queue不是线程安全的，在多线程环境中如需使用通常可以使用加锁的方式，但是大量的切换会有一定开销。  
可以考虑无锁队列。  
无锁编程是指在不使用锁的情况下，在多线程环境下实现多变量的同步。即在没有线程阻塞的情况下实现同步。这样可以避免竞态、死锁等问题。
它通常依赖于原子操作。 

## CAS
CAS是指Compare-and-swap或Compare-and-Set
CAS是一个原子操作，用于多线程环境下的同步。它比较内存中的内容和给定的值，只有当两者相同时（说明其未被修改），才会修改内存中的内容。

## ABA问题
在多线程环境中，使用lock-free的CAS时，如果一个线程对变量修改2次，第2次修改后的值和第1次修改前的值相同，那么可能就会出现ABA问题。以上面的例子为例：
假设有两个线程P1和P2，P1执行完int oldval=val后被其他线程抢占。P2线程在此期间修改了val的值（可能多次修改），但最终val的值和修改前一样。当P1线程之后运行CAS函数时，并不能发现这个问题。这就是ABA问题。

解决方法
一个常用的方法是添加额外的“tag”或“stamp”位来标记是指针是否被修改过。 

## 现有实现
- boost实现
- github开源实现  
[source](https://github.com/cameron314/concurrentqueue)   
[性能数据](https://moodycamel.com/blog/2014/a-fast-general-purpose-lock-free-queue-for-c++.htm)  
[设计说明](https://moodycamel.com/blog/2014/detailed-design-of-a-lock-free-queue.htm)  
