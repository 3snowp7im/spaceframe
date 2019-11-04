#pragma once

#include <memory>

namespace sf {

  class log {
    static std::shared_ptr<void> impl;
  public:
    static void debug(const char*, ...);
    static void info(const char*, ...);
    static void warn(const char*, ...);
    static void error(const char*, ...);
  };

}
