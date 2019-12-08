#pragma once

#include <array>
#include <stdexcept>
#include <sf/mpf.h>
#include <sf/mpz.h>
#include <sf/qtrn.h>
#include <sf/vec3.h>
#include <sf/vec4.h>

namespace sf {

  class face {
    static void init();
    static std::array<vec3<mpf>, 3> vertices;
  public:
    typedef long coord_t;
    typedef long unsigned ucoord_t;
    typedef vec4<coord_t> coords_t;
    struct range {
      vec4<ucoord_t> start;
      ucoord_t len;
    };
    typedef vec4<mpf> vec_t;
    template <typename T> static vec3<T> vert_from_vec(const vec4<T>&);
    static coords_t coords_from_vec(const vec_t& vec);
    static vec3<mpf> point_from_vert(const vec3<coord_t>&);
    const static coord_t coord_max;
    const static unsigned coord_max_log2;
    face();
    face(const qtrn&);
    face& operator=(const face&);
    bool is_point_in_bounds(const vec3<mpf>&) const;
    sf::vec3<sf::mpf> face_pos_from_point(const vec3<mpf>&) const;
    vec_t vec_from_face_pos(const vec3<mpf>&) const;
    qtrn orientation;
    friend void sf::init();
  };

  template <typename T>
  inline vec3<T> face::vert_from_vec(const vec4<T>& vec) {
    return vec3<T>(vec[2], vec[0], vec[3]);
  }

}
