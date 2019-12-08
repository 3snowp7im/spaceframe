#pragma once

#include <sf/face.h>

namespace sf {
  namespace field {

    inline size_t level_count_from_lod(unsigned lod) {
      return face::coord_max_log2 - lod;
    }

  }
}
