#pragma once

#include <memory>

namespace spaceframe {

  class window {
  public:
    static void create(unsigned, unsigned, const std::string&);
    static void destroy();
    static void poll_events();
    static bool should_close();
    static void swap_buffers();
  private:
    static void release(void*);
    static std::unique_ptr<void, decltype(&release)> impl;
  };

}
