#pragma once

#include <array>
#include "mpf.h"
#include "qtrn.h"
#include "vec3.h"
#include "vec4.h"

namespace sf {

  class mat4 {
    std::array<mpf, 16> m;
  public:
    static mat4 translate(const vec3&);
    static mat4 rotate(const qtrn&);
    static mat4 project(const mpf&, const mpf&, const mpf&, const mpf&);
    static const mat4 identity;
    mat4();
    mat4(const vec4&, const vec4&, const vec4&, const vec4&);
    mat4(
      const mpf&, const mpf&, const mpf&, const mpf&,
      const mpf&, const mpf&, const mpf&, const mpf&,
      const mpf&, const mpf&, const mpf&, const mpf&,
      const mpf&, const mpf&, const mpf&, const mpf&
    );
    mat4 norm() const;
    mpf& operator[](size_t n);
    const mpf& operator[](size_t n) const;
    mat4 operator/(const mpf&) const;
    mat4 operator/=(const mpf&) const;
    vec3 operator*(const vec3&) const;
    vec4 operator*(const vec4&) const;
    mat4 operator*(const mat4&) const;
    template <typename T> operator std::array<T, 16>() const;
  };

  template <typename T>
  inline mat4::operator std::array<T, 16>() const {
    std::array<T, 16> array;
    for (int i = 0; i < m.size(); i++) {
      array[i] = static_cast<T>(m[i]);
    }
    return array;
  }

}
