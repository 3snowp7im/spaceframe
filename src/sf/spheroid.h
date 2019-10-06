#pragma once

#include <array>
#include "mat4.h"
#include "tetra.h"
#include "vec4.h"

namespace sf {

  class spheroid {
    const tetra& tetra_from_pos(const vec3&) const;
  public:
    static vec3 point_to_tetra_space(const vec3&);
    static const std::array<tetra, 20> tetras;
    spheroid(tetra::coord_t);
    const tetra::coord_t r;
  };

  inline spheroid::spheroid(tetra::coord_t r)
    : r(r)
  {
  }

}
