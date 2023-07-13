#pragma once

#include <memory>  // for shared_ptr
#include <string>  // for string

 

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#include <spdlog/spdlog.h> 
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace mylogger {

class Logger {
 public:
  static Logger &GetInstance() {
    static Logger instance;
    return instance;
  }
  spdlog::logger *get() const { return logger_ptr_.get(); }

 private:
  Logger() {
    auto *env = std::getenv("LOG_MODE");
    if (env) {
      std::string envstr(env);
      if (envstr == "FILE") {
        logger_ptr_ = spdlog::basic_logger_mt("console", "spdlog.txt", true);
      } else {
        logger_ptr_ = spdlog::stdout_color_mt("console");
      }
    } else {
      logger_ptr_ = spdlog::stdout_color_mt("console");
    }
  }

  std::shared_ptr<spdlog::logger> logger_ptr_;
};

}  // namespace mylogger

#define LOG_TRACE(message) \
  SPDLOG_LOGGER_TRACE(Logger::GetInstance().get(), message)
#define LOG_DEBUG(message) \
  SPDLOG_LOGGER_DEBUG(Logger::GetInstance().get(), message)
#define LOG_INFO(message) \
  SPDLOG_LOGGER_INFO(Logger::GetInstance().get(), message)
#define LOG_WARN(message) \
  SPDLOG_LOGGER_WARN(Logger::GetInstance().get(), message)
#define LOG_ERROR(message) \
  SPDLOG_LOGGER_ERROR(Logger::GetInstance().get(), message)

 
