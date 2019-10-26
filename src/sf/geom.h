#pragma once

#include <vector>
#include "tetra.h"

namespace sf {
  namespace geom {

    size_t range_count_from_lod(size_t);

    std::vector<int> vertices_from_lod(size_t);

    tetra::range_t viewable_range_from_vec(const tetra::vec_t&);

  }
}
