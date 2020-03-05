#include <glog/logging.h>
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);  // 初始化GLog库
  FLAGS_log_dir = "/tmp";              // 将日志文件输出到本地
  FLAGS_logtostderr = 1;  //将使得日志信息记录到stderr而不会保存到本地日志文件中

  FLAGS_stderrthreshold = 3;  //设置记录到stderr的log的级别
  FLAGS_minloglevel = 0;      //设置需要记录log的级别

  // 常用的flag有：(可以通过环境变量设置 GLOG_xxxx)

  // logtostderr （ bool ，默认为 false ）
  // 日志输出到stderr，不输出到日志文件。
  // colorlogtostderr （ bool ，默认为 false ）
  // 输出彩色日志到stderr。
  // stderrthreshold （ int ，默认为2，即 ERROR ）
  // 将大于等于该级别的日志同时输出到stderr。日志级别 INFO, WARNING, ERROR, FATAL
  // 的值分别为0、1、2、3。 minloglevel （ int ，默认为0，即 INFO ）
  // 打印大于等于该级别的日志。日志级别的值同上。
  // log_dir （ string ，默认为 "" ）
  // 指定输出日志文件的目录。
  // v （ int ，默认为0）
  // 显示所有 VLOG(m) 的日志， m 小于等于该flag的值。会被 --vmodule 覆盖。

  LOG(INFO) << "There is INFO !!!";
  LOG(WARNING) << "There is WARNING !!!";
  LOG(ERROR) << "There is error !!!";
  // LOG(FATAL) << "There is FATAL !!!"; // FATAL 导致程序退出，打印调用堆栈

  // 条件输出
  for (int i = 0; i < 20; i++) {
    LOG_IF(INFO, i > 15) << "i > 15： " << i;  //当i > 15时，记录Log;
  }
  // 周期输出
  for (int i = 0; i < 20; i++) {
    LOG_EVERY_N(INFO, 3) << "i: " << i;  //每隔3次输出一次信息；
  }
  // 限制输出次数
  for (int i = 0; i < 20; i++) {
    LOG_FIRST_N(INFO, 4) << "i: " << i;  // 输出前4次Log
  }

  // 条件加周期记录
  for (int i = 0; i < 20; i++) {
    LOG_IF_EVERY_N(INFO, i > 10, 3) << "i > 10, i: " << i;  //当i > 10之后，每隔3次输出一次信息；
  }

  // 支持调试模式
  // 调试模式的宏仅在调试模式下有效，在非调试模式编译时为空。
  // 在宏前面加D就支持了调试模式；
  // DLOG(), DLOG_IF(), DLOG_EVERY_N(), …

  // 崩溃处理
  // 当程序出现崩溃时，GLog也可以提供Bug定位支持。
  // 通过google::InstallFailureSignalHandler()安装信号处理程序，当程序出现崩溃时，会输出崩溃的位置等相关信息。
  return 0;
}