#pragma once

#include <array>
#include <stdexcept>
#include <sf/mpf.h>
#include <sf/qtrn.h>
#include <sf/vec3.h>
#include <sf/vec4.h>

namespace sf {

  class face {
    static void init();
    static std::array<vec3<mpf>, 3> vert_array;
    class vert_access {
    public:
      const vec3<mpf>& operator[](size_t) const;
      friend face;
    };
  public:
    typedef long coord_t;
    typedef unsigned long ucoord_t;
    typedef vec4<coord_t> range_t;
    typedef vec4<mpf> vec_t;
    const static coord_t coord_max;
    constexpr static vert_access verts = vert_access();
    face();
    face(const qtrn&);
    face& operator=(const face&);
    bool is_point_in_bounds(const vec3<mpf>&) const;
    sf::vec3<sf::mpf> face_pos_from_point(const vec3<mpf>&) const;
    vec_t vec_from_face_pos(const vec3<mpf>&) const;
    qtrn orientation;
    friend void sf::init();
    friend const vec3<mpf>& vert_access::operator[](size_t i) const;
  };

}
