#pragma once

#include <array>
#include <stdexcept>
#include "mpf.h"
#include "qtrn.h"
#include "vec3.h"
#include "vec4.h"

namespace sf {

  class tetra {
    static void init();
    static std::array<vec3<mpf>, 3> vertex_array;
  public:
    typedef long coord_t;
    typedef vec4<coord_t> range_t;
    typedef vec4<mpf> vec_t;
    static const coord_t coord_max;
    static const class vertex_access {
      static bool constructed;
    public:
      vertex_access();
      const vec3<mpf>& operator[](size_t) const;
    } vertices;
    tetra();
    tetra(const qtrn&);
    tetra& operator=(const tetra&);
    bool is_vertex_in_bounds(const vec3<mpf>&) const;
    vec_t vec_from_vertex(const vec3<mpf>&) const;
    qtrn orientation;
    friend void sf::init();
    friend const vec3<mpf>& vertex_access::operator[](size_t i) const;
  };

}
