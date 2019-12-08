#pragma once

#include <memory>
#include "input.h"

namespace spaceframe {

  class window {
    static void release(void*);
    static std::unique_ptr<void, decltype(&release)> impl;
  public:
    static void create(unsigned, unsigned, const std::string&);
    static void destroy();
    static void poll_events();
    static bool get_should_close();
    static void set_should_close();
    static void swap_buffers();
    static input::key_state_t get_key_state(input::key_t);
  };

}
