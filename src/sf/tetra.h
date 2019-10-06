#pragma once

#include <array>
#include "qtrn.h"
#include "vec3.h"

namespace sf {

  class tetra {
  public:
    typedef long long coord_t;
    struct coords {
      coords(const coord_t&, const coord_t&, const coord_t&, const coord_t&);
      coord_t a, b, c, d;
    };
    static const std::array<vec3, 3> face_vertices;
    tetra(const qtrn&);
    bool is_point_in_bounds(const vec3&) const;
    coords point_to_coords(const vec3&) const;
    const qtrn orientation;
  };

  inline tetra::coords::coords(const coord_t& a, const coord_t& b, const coord_t& c, const coord_t& d)
    : a(a), b(b), c(c), d(d)
  {
  }

}
