#include <stdio.h>
#include <stdarg.h>

//
// c style 
// va_list va_start va_arg va_end
// 
// call: printf("%f\n", SumOfFloat(3, 1.2f, 3.4, 5.6));  // 10.200000 

double SumOfFloat(int count, ...) {
    va_list ap;
    double sum = 0;
    va_start(ap, count);            // 获得变长列表的句柄ap
    for(int i = 0; i < count; i++)
        sum += va_arg(ap, double);  // 每次获得一个参数
    va_end(ap);
    return sum;
}
/////////////////////////////////////////////////////////////////////////

//
// 变长模板
//
template <typename... Elements> class tuple;        // 变长模板的声明
template<typename Head, typename... Tail>           // 递归的偏特化定义
class tuple<Head, Tail...> : private tuple<Tail...> {
    Head head;
};
template<> class tuple<> {};                        // 边界条件

/////////////////////////////////////////////////////////////////////////

//
// 非参数模板
//
// Multiply<2, 3, 4, 5>::val
// Multiply<2, 3, 4, 5>::val
//
template <long... nums> struct Multiply; 

template <long first, long... last>
struct Multiply<first, last...> {
    static const long val = first * Multiply<last...>::val;
};
template<> 
struct Multiply<> {
    static const long val = 1;
};



int main() {
    printf("%f\n", SumOfFloat(3, 1.2f, 3.4, 5.6));  // 10.200000
}
