#include <algorithm>  //copy
#include <chrono>
#include <complex>
#include <fstream>
#include <functional>  //multiplies()
#include <iomanip>     //setpricision()
#include <iostream>    //cout
#include <iterator>    //ostream_iterator
#include <numeric>     //iota
#include <ratio>
#include <string>  //string
#include <valarray>
#include <vector>  //vector
#include <random>

using namespace std;
using namespace chrono;
using namespace literals;

template <typename T>
void print(const valarray<T> values, size_t perline = 8, size_t width = 8) {
  size_t n{};
  for (const auto& value : values) {
    cout << setw(width) << value << " ";
    if (++n % perline == 0) cout << endl;
  }
  if (n % perline != 0) cout << endl;
  cout << endl;
}

// output the exact interval in seconds for a time_point<>
template <typename TimePoint>
void print_timepoint(const TimePoint& tp, size_t places = 0) {
  auto elapsed = tp.time_since_epoch();  // chrono::duration object
  auto seconds =
      chrono::duration_cast<chrono::duration<double>>(elapsed).count();  // second是double类型
  cout << fixed << setprecision(places) << seconds << " seconds\n";
}

void test_complex() {  // 10.5 复数
  {
    complex<double> z1{2, 5};
    complex<double> z;

    using namespace literals::complex_literals;
    z = 5.0 + 3i;
    z = 5.0 + 1i;  // 5.0+i是错误的
  }

  {
    complex<double> z{1.5, -2.5};
    z.imag(99);
    z.real(-4.5);
    cout << "Real part: " << z.real() << " Imaginary part: " << z.imag() << endl;
  }

  {
    complex<double> z1, z2, z3;
    // cin>>z1>>z2>>z3
    //-4 6 (-3, 7)
    //===> z1=-4+0i; z2=6+0i; z3=-3+7i
  }

  {  // 10.5.2 复数计算
    using namespace literals::complex_literals;

    complex<double> z{1, 2};
    // auto z1 = z +3;//compile error, 3 => 3.0
    auto z1 = z + 3.0;

    // auto z2 = z*z + (2.0+4.0i);//compile error, 编译器缺陷gcc7.1.2
    complex<double> z2 = (2.0 + 4.0i);
    z2 += z * z;

    auto z3 = z1 - z2;
    z /= z1;
  }
  {  // 10.5.3 比较
    //#include <cmath>//#include <complex>已经包含了cmath头文件
    complex<double> z1{3, 4};
    complex<double> z2{4, -3};
    cout << boolalpha << (z1 == z2) << " ";
    //<< (z1!=(3.0+4i)) << " "; // gcc7.1.2不支持
    //<< (z2==(4.0-3i)) << '\n'; // gcc7.1.2不支持
    cout << boolalpha << (abs(z1) == abs(z2)) << " ";
    //<< abs(z2 + (4.0+9i)); // gcc7.1.2不支持

    complex<double> zc{0.0, acos(-1)};
    cout << (exp(zc) + 1.0) << '\n';  //
  }
  {  // 10.5.4 复数综合示例, Ex10_06.cpp

    const int width{100}, height{100};  // Image width and height
    size_t count{100};                  // Iterate count for recursion
    char image[width][height];
    auto start_time = chrono::steady_clock::now();  // time_point object for start
    complex<double> c{-0.7, 0.27015};               // Constant in z = z*z + c

    for (int i{}; i < width; ++i)  // Iterate over pixels in the width
    {
      for (int j{}; j < height; ++j)  // Iterate over pixels in the height
      {
        // Scale real and imaginary parts to be between -1 and +1
        auto re = 1.5 * (i - width / 2) / (0.5 * width);
        auto im = (j - height / 2) / (0.5 * height);
        complex<double> z{re, im};  // Point in the complex plane
        image[i][j] = ' ';          // Point not in the Julia set
        // Iterate z=z*z+c count times
        for (size_t k{}; k < count; ++k) {
          z = z * z + c;
        }
        if (abs(z) < 2.0)     // If point not escaping...
          image[i][j] = '*';  // ...it's in the Julia set
      }
    }
    auto end_time = chrono::steady_clock::now();  // time_point object for end
    auto elapsed = end_time - start_time.time_since_epoch();
    cout << "Time to generate a Julia set with " << width << "x" << height << " pixels is ";
    print_timepoint(elapsed, 9);

    cout << "The Julia set looks like this:\n";
    for (size_t i{}; i < width; ++i) {
      for (size_t j{}; j < height; ++j) cout << image[i][j];
      cout << '\n';
    }
  }
}

void test_chrono() {  // 10.4 时间模板
  chrono::duration<int, milli> /*1 tick=1ms*/ IBM650_divide{15};
  chrono::duration<int> /*默认1tick=1s*/ minute{60};
  chrono::duration<double, ratio<60>> /*1tick=1min*/ hour{60};
  chrono::duration<long, micro> /*1tick=1us*/ milisec{1000L};
  chrono::duration<double, ratio<1, 5>> tiny{5.5};

  {  // duration计算
    chrono::duration<double, ratio<1, 5>> tiny{5.5};
    chrono::microseconds very_tiny{100};
    ++tiny;
    very_tiny--;
    cout << "tiny= " << tiny.count() << " verY_tiny = " << very_tiny.count() << endl;
  }

  {  //混合计算，则以更为精细的单位为计算结果的单位。
    chrono::milliseconds ten_minites{600000};
    chrono::minutes half_hour(30);
    auto total = ten_minites + half_hour;  // total 的单位为ms
    cout << "total = " << total.count() << endl;
  }
  {                                              //单位的转换
    chrono::duration<int, ratio<1, 5>> d1{50};   // 10s
    chrono::duration<int, ratio<1, 10>> d2{50};  // 5s
    chrono::duration<int, ratio<1, 3>> d3{45};   // 15s
    chrono::duration<int, ratio<1, 6>> d4{60};   // 10s
    d2 += d1;
    // d1+=d2; //d1<1,5> 和 d2<1, 10>不match, d2<1,10>到d1<1,5>的单位转换不可行。
    d1 += chrono::duration_cast<chrono::duration<int, ratio<1, 5>>>(d2);
    // d1+=d3; // d1<1,5>和d3<1,3>不match，d3<1,3>到d1<1,5>的单位转换不可行。
    d1 += chrono::duration_cast<chrono::duration<int, ratio<1, 5>>>(d3);
    d4 += d3;
    cout << "d1=" << d1.count() << "; d2=" << d2.count() << "; d3=" << d3.count()
         << "; d4=" << d4.count() << endl;
  }
  {
    chrono::duration<int, ratio<1, 5>> d1{50};
    chrono::duration<int, ratio<1, 10>> d2{53};
    d2 = d1;  // d1=10s被隐式转换为d2的单位<1,10>, 即100
  }
  {  // duration比较
    chrono::duration<int, ratio<1, 5>> d1{50};
    chrono::duration<int, ratio<1, 10>> d2{50};
    chrono::duration<int, ratio<1, 3>> d3{45};
    if ((d1 - d2) == (d3 - d1)) {
      cout << "both duration are " << chrono::duration_cast<chrono::seconds>(d1 - d2).count()
           << " seconds" << endl;
    }
  }
  {  // duration常量
    using namespace literals::chrono_literals;
    // or
    using namespace chrono;

    // chrono::seconds == chrono::duration<long long, ratio<1,1>>
    chrono::seconds elapsed{10};  // 10 seconds
    elapsed += 2min;
    elapsed -= 15s;
    // elapsed += 10ns; // compile error!

    auto some_time = 10s;
    elapsed = 3min - some_time;  // 170

    some_time *= 2;
    const auto FIVE_SEC = 5s;
    elapsed = 2s + (elapsed - FIVE_SEC) / 5;  // 35
  }
  {  // 10.4.2 时钟和时间点timepoint
    cout << boolalpha << chrono::system_clock::is_steady << endl;

    chrono::system_clock::time_point tp_sys1;          // default object - the epoch
    chrono::time_point<chrono::system_clock> tp_sys2;  // default object - the epoch

    using Clock = chrono::steady_clock;
    using TimePoint = chrono::time_point<Clock>;  // or using TimePoint = Clock::time_point;
    using namespace literals::chrono_literals;

    TimePoint tp1{chrono::duration<int>(20)};  // epoch + 20 seconds
    print_timepoint(tp1);

    TimePoint tp2{3min};  // epoch + 3min
    print_timepoint(tp2);

    TimePoint tp3{2h};  // epoch + 2h
    print_timepoint(tp3);

    TimePoint tp4{5500us};  // epoch + 00055 seconds
    print_timepoint(tp4);

    //强制以chrono::minutes作为单位并不好，也没有必要，比如：
    chrono::time_point<chrono::system_clock, chrono::minutes> tp{2h};

    {  // 2. tp对象的持续时间
      using Clock = chrono::steady_clock;
      using TimePoint = Clock::time_point;
      TimePoint tp1{chrono::duration<int>(20)};  // epoch + 20seconds
      print_timepoint(tp1);
      auto elapsed = tp1.time_since_epoch();  // chrono::duration for the time interval,
                                              // 但类型具体类型未知，我们强制转换为ns单位的duration
      auto ticks_ns = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
    }
    {                          // 3. tp的算术运算 Ex10_04.cpp
      using namespace chrono;  // using chrono不能达到目的

      time_point<steady_clock> tp1{duration<int>(20)};
      cout << "tp1 is ";
      print_timepoint(tp1);

      time_point<system_clock> tp2{3min};
      cout << "tp2 is ";
      print_timepoint(tp2);

      time_point<high_resolution_clock> tp3{2h};
      cout << "tp3 is ";
      print_timepoint(tp3);

      auto tp4 = tp2 + tp3.time_since_epoch();
      cout << "tp4 is tp2 with tp3 added: ";
      print_timepoint(tp4);

      cout << "tp1 + tp2 is ";
      print_timepoint(tp1 + tp2.time_since_epoch());

      tp2 += duration<time_point<system_clock>::rep, milli>{20'000};
      cout << "tp2 incremented by 20,000 millisecond is ";
      print_timepoint(tp2);

      // cast丢精度
      using TimePoint = time_point<system_clock, seconds>;
      TimePoint tp_sec{75s};                           // tp_sec{75}不能通过编译.
      auto tp_min = time_point_cast<minutes>(tp_sec);  // 75s变为60s, 丢了15s
      print_timepoint(tp_min);
    }

    {  // 4. 比较timepoint
      using TimePoint1 = chrono::time_point<chrono::system_clock>;
      using TimePoint2 = chrono::time_point<chrono::system_clock, chrono::minutes>;

      TimePoint1 tp1{120s};
      TimePoint2 tp2{2min};

      cout << "tp1 ticks: " << tp1.time_since_epoch().count()
           << "; tp2 ticks: " << tp2.time_since_epoch().count() << endl;

      cout << "tp1 is " << ((tp1 == tp2) ? "equal" : "not equal") << " to tp2" << endl;
    }
    {  // 5. clock的操作，动起来.
      using Clock = chrono::system_clock;
      auto instant = Clock::now();  // return a time_point<Clock>
      time_t the_time = Clock::to_time_t(instant);
      cout << put_time(localtime(&the_time),
                       "The time now is: %R.%nToday is %A %e %B %Y. The time zone is %Z.%n");

      time_t t = Clock::to_time_t(Clock::now());
      auto p_tm = localtime(&t);
      cout << "Time: " << p_tm->tm_hour << ':' << setfill('0') << setw(2) << p_tm->tm_min << endl;
    }
    {  // 6. 定时执行.
      auto start_time = chrono::steady_clock::now();

      for (int i = 0; i < 100000; ++i)
        for (int j = 0; j < 10000; ++j)
          ;

      auto end_time = chrono::steady_clock::now();
      auto elapsed = end_time - start_time.time_since_epoch();
      cout << "Time consumed: ";
      print_timepoint(elapsed, 2);
    }
  }
}

void test_valarray() {  // 10.3 valarray
  {
    valarray<int> numbers(15);  // 15个0
    valarray<size_t> sizes{1, 2, 3};
    valarray<double> values;
    valarray<double> data(3.14, 10);  // 10个3.14

    int vals[]{2, 4, 6, 8, 10, 12, 14};
    valarray<int> vals1{vals, 5};     //前5个元素, vals是数组vals[]的首地址.
    valarray<int> val2{vals + 1, 4};  // 4, 6, 8, 10

    // 10.3.1 valarray基本操作
    valarray<size_t> sizes_3{1, 2, 3};
    valarray<size_t> sizes_4{2, 3, 4, 5};
    sizes_3.swap(sizes_4);
    swap(sizes_3, sizes_4);
    cout << "The average of the elements in sizes_4" << sizes_4.sum() / sizes_4.size() << endl;

    // shift
    valarray<int> d1{
        1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    auto d2 = d1.shift(2);
    for (int n : d2) cout << n << ' ' << endl;
    auto d3 = d1.shift(-3);
    copy(begin(d3), end(d3), ostream_iterator<int>{cout, " "});
    cout << endl;

    auto d4 = d1.cshift(2);
    auto d5 = d1.cshift(-3);

    // valarray.apply()
    valarray<double> time{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};  // unit: seconds
    auto distance = time.apply([](double t) {
      const static double g{32.0};
      return 0.5 * g * t * t;
    });
    // compile error
    // const double g{32.0};
    // auto distance = time.apply([g](double t){ const static double g{32.0}; return 0.5*g*t*t;});
    // Ex10_2.cpp
    const static double g{32.0};  // unit: ft/sec/sec
    double height{2722};          // unit: feet, building height for brick drop from
    double end_time{sqrt(2 * height / g)};
    size_t max_time{1 + static_cast<size_t>(end_time + 0.5)};

    valarray<double> times(max_time + 1);
    iota(begin(times), end(times), 0);
    *(end(times) - 1) = end_time;

    // Calculate distance each second
    auto temp = times.apply([](double t) { return 0.5 * g * t * t; });
    valarray<double> distances = times.apply([](double t) { return 0.5 * g * t * t; });

    // Calculate speed each second
    valarray<double> v_fps = sqrt(distances.apply([](double d) { return 2 * g * d; }));

    // Lambda expression to output results
    auto print = [](double v) { cout << setw(6) << static_cast<int>(round(v)); };

    // Output the times - the last is a special case...
    cout << "Time(seconds): ";
    for_each(begin(times), end(times) - 1, print);
    cout << setw(6) << fixed << setprecision(2) << *(end(times) - 1);
    cout << "\nDistances(feet):";
    for_each(begin(distances), end(distances), print);

    cout << "\nVelocity(fps): ";
    for_each(begin(v_fps), end(v_fps), print);

    valarray<double> v_mph = v_fps.apply([](double v) { return v * 60 / 88; });
    cout << "\nVelocity(mph): ";
    for_each(begin(v_mph), end(v_mph), print);

    cout << endl;
  }
  {
      // 10.3.2 一元运算符
  } {  // 10.3.4 二元运算符
    {
      valarray<int> even{2, 4, 6, 8};
      valarray<int> odd{3, 5, 7, 9};
      valarray<int> r1 = even + 2;  //不能使用auto
      print(r1, 4, 3);
      valarray<int> r2 = 2 * r1 + odd;  //不能使用auto
      print(r2, 4, 3);
      r1 += 2 * odd - 4 * (r2 - even);
      print(r1, 4, 3);

      odd <<= 3;
      print(odd, 4, 3);
      // print(odd<<3, 4, 3); // compile error!
    }
    // 10.3.5 access valarray
    valarray<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(data, 3, 3);
    data[1] = data[2] + data[3];
    print(data, 3, 3);
    data[3] *= 2;
    print(data, 3, 3);
    data[4] = ++data[5] - data[2];
    print(data, 3, 3);

    {                           // 1. 创建切片
      slice my_slice{3, 4, 2};  // index=3, size=4, stride/step=2

      valarray<int> data(15);
      iota(begin(data), end(data), 1);
      print(data, 5, 3);
      size_t start{2}, size(3), stride{5};
      // d_slice是slice_array类型
      // references data[2], data[7], data[12]
      auto d_slice = data[slice{start, size, stride}];

      slice_array<int> copy_slice{d_slice};

      valarray<int> more{2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6};
      data[slice{0, 5, 1}] = 99;
      print(data, 5, 3);
      data[slice{10, 5, 1}] = more;
      print(data, 5, 3);
      // data[slice{0,4,5}]=0; //为第一列赋值0; size=4故意多了一个，运行正常
      // print(data, 5, 3);
    }

    {
      valarray<int> data(15);
      iota(begin(data), end(data), 1);
      print(data, 5, 3);
      size_t start{2}, size(3), stride{5};
      // d_slice是slice_array类型
      // references data[2], data[7], data[12]
      auto d_slice = data[slice{start, size, stride}];

      d_slice += valarray<int>{10, 20, 30};  //使用复合赋值运算符操作data第二列
      print(data, 5, 3);

      valarray<int> factors{22, 17, 10};
      data[slice{0, 3, 5}] *= factors;  // values of the 1st colum: 22 102 110
      print(data, 5, 3);
    }
    {
      valarray<int> data(15);
      iota(begin(data), end(data), 1);
      print(data, 5, 3);
      slice row3{10, 5, 1};
      data[row3] *= valarray<int>(3, row3.size());
      print(data, 5, 3);
    }
    {
      valarray<int> data(15);
      iota(begin(data), end(data), 1);
      print(data, 5, 3);

      auto col{data[slice{4, 3, 5}]};            // col will be type slice_array
      valarray<int> col5{data[slice{4, 3, 5}]};  // convert slice_array to valarray
      data[slice{1, 3, 5}] += col5;
      data[slice{3, 3, 5}] += col5;
      print(data, 5, 3);
    }
  }  // end of 10.3.5
}

void test_basic() {
  int s1[10], s2[10];

  fill(s1, end(s1), 1);
  copy(s1, end(s1), s2);
  iota(s1, end(s1), 1);

  reverse(begin(s1), end(s1));
  replace(begin(s1), end(s1), 3, 100);

  rotate(begin(s1), s1 + 3, end(s1));

  random_shuffle(begin(s1), end(s1));

  std::mt19937 g(std::random_device{}());
  shuffle(begin(s1), end(s1), g);

  sort(begin(s1), end(s1));

  copy(s1, end(s1), s2);
  copy(s2, end(s2), ostream_iterator<int>(cout, " , "));
  cout << endl;

  cout << "input intergers ,press ctrl+z to end with" << endl;
  vector<int> ivec;
  copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(ivec));
  copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " , "));
}

int main(void) {
  {
    ///======== iota: Store increasing sequence
    ///======== copy: Copy range of elements

    vector<double> data(9);
    double initial{-2.5};
    iota(begin(data), end(data), initial);
    copy(begin(data), end(data), ostream_iterator<double>{cout << fixed << setprecision(1), " "});
    cout << endl;

    string text{"This is text"};
    iota(begin(text), end(text), 'K');
    cout << text << endl;

    vector<string> words(8);
    iota(begin(words), end(words), "mysterious");
    // iota(begin(words), end(words), string{"mysterious"});//compile error, T should support
    // operator++
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
    cout << endl;
  }

  {
    ///======== accumulate() : Accumulate values in range
    vector<int> values{2, 1, 12, 3, 5, 1, 2, 7, 1, 8};
    int min{2};
    auto sum = accumulate(begin(values), end(values), 0, [min](int sum, int v) {
      if (v < min)
        return sum;
      else
        return sum + v;
    });

    auto product = accumulate(begin(values), end(values), 1,
                              multiplies<int>());  // 30030

    vector<string> numbers{"one", "two",   "three", "four", "five",
                           "six", "seven", "eight", "nine", "ten"};
    auto s = accumulate(begin(numbers), end(numbers), string{}, [](string& str, string& element) {
      if (element[0] == 't') return str + ' ' + element;
      return str;
    });  // result: " two three ten"

    vector<int> num = {1, 2, 3, 10, 11, 12};
    auto sx = accumulate(begin(num), end(num), string{"The numbers are"},
                         [](string str, int n) { return str + ": " + to_string(n); });
    cout << sx << endl;  // output: The numbers are: 1: 2: 3: 10: 11: 12
  }

  {
    ///======== inner_product() : Compute cumulative inner product of range
    // 10.2.3 内积
    vector<int> v1(4);
    vector<int> v2(4);
    iota(begin(v1), end(v1), 2);
    iota(begin(v1), end(v1), 3);
    cout << inner_product(begin(v1), end(v1), begin(v2), 0) << endl;
    // output: 570

    vector<double> data{0.5, 0.75, 0.85};
    auto result1 = inner_product(begin(data), end(data), begin(data), 0);
    double result2 = inner_product(begin(data), end(data), begin(data), 0);
    auto result3 = inner_product(begin(data), end(data), begin(data), 0.0);
    cout << result1 << " " << result2 << " " << result3 << endl;

    // 新的内积使用方法
    iota(begin(v1), end(v1), 0);
    iota(begin(v2), end(v2), 0);
    cout << inner_product(begin(v1), end(v1), begin(v2), 1) << endl;  // output: 111
    cout << inner_product(begin(v1), end(v1), begin(v2), 1, plus<>() /*后做*/,
                          multiplies<>() /*先做*/)
         << endl;
    cout << inner_product(begin(v1), end(v1), begin(v2), 1, multiplies<>(), plus<>()) << endl;
  }

  {  // 10.2.4 相邻差
    vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
    cout << "Difference: ";
    adjacent_difference(begin(data), end(data), ostream_iterator<int>{cout, " "});
    cout << endl;

    vector<int> data2{2, 3, 5, 7, 11, 13, 17, 19};
    cout << "Products: ";
    adjacent_difference(begin(data2), end(data2), ostream_iterator<int>{cout, " "}, multiplies<>());
    cout << endl;

    // fibonacci by adjacent_difference()
    vector<size_t> fib(15, 1);
    adjacent_difference(begin(fib), end(fib) - 1, begin(fib) + 1, plus<>());
    copy(begin(fib), end(fib), ostream_iterator<size_t>{cout, " "});
    cout << endl;

    // fibonacci by adjacent_difference(): wrong implementation
    adjacent_difference(begin(fib), end(fib), ostream_iterator<size_t>{cout, " "}, plus<>());
    cout << endl;
  }

  {  // 10.2.5 partial_sum
    vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
    // 前1个元素的和; 前2个元素的和; ...; 前n个元素的和
    cout << "Partial sums: ";
    partial_sum(begin(data), end(data), ostream_iterator<int>{cout, " "});
    cout << endl;  // Partial sums: 2 5 10 17 28 41 58 77

    cout << "Original data: ";
    copy(begin(data), end(data), ostream_iterator<int>{cout, " "});

    adjacent_difference(begin(data), end(data), begin(data));
    cout << "\nDifference: ";
    copy(begin(data), end(data), ostream_iterator<int>{cout, " "});

    cout << "\nPartial Sums: ";
    partial_sum(begin(data), end(data), ostream_iterator<int>{cout, " "});
    cout << endl;
  }
  {
    // 10.2.6 max, min
    // max_element, 返回迭代器
    vector<int> data{2, 12, 3, 5, 17, -11, 113, 117, 19};
    cout << "From values ";
    copy(begin(data), end(data), ostream_iterator<int>{cout, " "});
    auto min = min_element(begin(data), end(data));
    auto max = max_element(begin(data), end(data));
    cout << "\n Min = " << *min << "Max = " << *max << endl;

    auto pr = minmax_element(begin(data), end(data));
    cout << "\n Min = " << *pr.first << "Max = " << *pr.second << endl;

    auto words = {string{"one"}, string{"two"},   string{"three"}, string{"four"}, string{"five"},
                  string{"six"}, string{"seven"}, string{"eight"}};  // initializer_list

    auto prx =
        minmax(words, [](const string& s1, const string& s2) { return s1.back() < s2.back(); });
    cout << "\n Min = " << prx.first << "Max = " << prx.second << endl;
  }

  return 0;
}
