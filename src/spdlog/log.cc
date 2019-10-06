#include <cstdarg>
#include <vector>
#include <spdlog/spdlog.h>
#include "../spaceframe/log.h"

class log_wrapper {
public:
  log_wrapper(std::shared_ptr<spdlog::logger>&& logger) : logger(logger) {}
  std::shared_ptr<spdlog::logger> logger;
};

static void init(std::shared_ptr<void>& impl) {
  if (impl == nullptr) {
    impl.reset(new log_wrapper(spdlog::stdout_color_mt("spaceframe")));
    spdlog::set_level(spdlog::level::debug);
  }
}

void spaceframe::log::debug(const char* fmt, ...) {
  init(impl);
  va_list args;
  va_start(args, fmt);
  ssize_t size = vsnprintf(nullptr, 0, fmt, args) + 1;
  va_end(args);
  std::vector<char> buf(size);
  va_start(args, fmt);
  vsnprintf(&buf[0], size, fmt, args);
  va_end(args);
  static_cast<log_wrapper*>(impl.get())->logger->debug(&buf[0]);
}

void spaceframe::log::info(const char* fmt, ...) {
  init(impl);
  va_list args;
  va_start(args, fmt);
  ssize_t size = vsnprintf(nullptr, 0, fmt, args) + 1;
  va_end(args);
  std::vector<char> buf(size);
  va_start(args, fmt);
  vsnprintf(&buf[0], size, fmt, args);
  va_end(args);
  static_cast<log_wrapper*>(impl.get())->logger->info(&buf[0]);
}

void spaceframe::log::warn(const char* fmt, ...) {
  init(impl);
  va_list args;
  va_start(args, fmt);
  ssize_t size = vsnprintf(nullptr, 0, fmt, args) + 1;
  va_end(args);
  std::vector<char> buf(size);
  va_start(args, fmt);
  vsnprintf(&buf[0], size, fmt, args);
  va_end(args);
  static_cast<log_wrapper*>(impl.get())->logger->warn(&buf[0]);
}

void spaceframe::log::error(const char* fmt, ...) {
  init(impl);
  va_list args;
  va_start(args, fmt);
  ssize_t size = vsnprintf(nullptr, 0, fmt, args) + 1;
  va_end(args);
  std::vector<char> buf(size);
  va_start(args, fmt);
  vsnprintf(&buf[0], size, fmt, args);
  va_end(args);
  static_cast<log_wrapper*>(impl.get())->logger->error(&buf[0]);
}

std::shared_ptr<void> spaceframe::log::impl = nullptr;
