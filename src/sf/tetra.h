#pragma once

#include <array>
#include "qtrn.h"
#include "vec3.h"

namespace sf {

  class tetra {
  public:
    static const std::array<vec3, 3> face_vertices;
    typedef long long coord_t;
    static const coord_t coord_max;
    struct coords {
      coords(coord_t, coord_t, coord_t, coord_t);
      coord_t a, b, c, d;
    };
    tetra(const qtrn&);
    bool is_point_in_bounds(const vec3&) const;
    coords point_to_coords(const vec3&) const;
    const qtrn orientation;
  };

  inline tetra::coords::coords(coord_t a, coord_t b, coord_t c, coord_t d)
    : a(a), b(b), c(c), d(d)
  {
  }

}
