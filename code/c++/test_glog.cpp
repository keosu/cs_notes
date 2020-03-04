#include <glog/logging.h>
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);  // 初始化GLog库
  FLAGS_log_dir = "/tmp";              // 将日志文件输出到本地
  FLAGS_logtostderr = 1;  //将使得日志信息记录到stderr而不会保存到本地日志文件中

  FLAGS_stderrthreshold = 3;  //设置记录到stderr的log的级别
  FLAGS_minloglevel = 0;      //设置需要记录log的级别

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