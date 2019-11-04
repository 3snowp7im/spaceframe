#pragma once

#include <sf/mpf.h>
#include <sf/vec3.h>

namespace sf {

  class qtrn {
    std::array<mpf, 4> xyzw;
  public:
    static qtrn from_axis_angle(const vec3<mpf>&, const mpf&);
    qtrn();
    qtrn(const mpf&, const mpf&, const mpf&, const mpf&);
    mpf length() const;
    qtrn unit() const;
    qtrn operator-() const;
    qtrn operator*(const qtrn&) const;
    vec3<mpf> operator*(const vec3<mpf>&) const;
    mpf& operator[](size_t n);
    const mpf& operator[](size_t n) const;
    template <typename T> qtrn operator/(const T&) const;
  };

  template <typename T>
  inline sf::qtrn sf::qtrn::operator/(const T& v) const {
    return qtrn(xyzw[0] / v, xyzw[1] / v, xyzw[2] / v, xyzw[3] / v);
  }

}
