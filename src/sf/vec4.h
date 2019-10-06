#pragma once

#include <array>
#include "mpf.h"
#include "vec3.h"

namespace sf {

  class vec4 {
    std::array<mpf, 4> xyzw;
  public:
    vec4(const mpf&, const mpf&, const mpf&, const mpf&);
    vec4(const vec3&, const mpf& = mpf(1));
    std::array<mpf, 4>::iterator begin();
    std::array<mpf, 4>::const_iterator begin() const;
    std::array<mpf, 4>::iterator end();
    std::array<mpf, 4>::const_iterator end() const;
    size_t size() const;
    mpf length() const;
    vec4 unit() const;
    void unitize();
    operator vec3() const;
    mpf& operator[](size_t n);
    const mpf& operator[](size_t n) const;
    template <typename T> operator std::array<T, 4>() const;
    template <typename T> vec4 operator*(const T&) const;
    template <typename T> vec4 operator/(const T&) const;
    template <typename T> vec4 operator/=(const T&) const;
  };

  inline sf::vec4::vec4(const mpf& x, const mpf& y, const mpf& z, const mpf& w)
    : xyzw({x, y, z, w})
  {
  }

  inline sf::vec4::vec4(const vec3& xyz, const mpf& w)
    : xyzw({xyz[0], xyz[1], xyz[2], w})
  {
  }

  template <typename T>
  inline vec4::operator std::array<T, 4>() const {
    return std::array<T, 4>({
      static_cast<T>(xyzw[0]),
      static_cast<T>(xyzw[1]),
      static_cast<T>(xyzw[2]),
      static_cast<T>(xyzw[3]),
    });
  }

  template <typename T>
  inline sf::vec4 sf::vec4::operator*(const T& v) const {
    return vec4(xyzw[0] * v, xyzw[1] * v, xyzw[2] * v, xyzw[3] * v);
  }

  template <typename T>
  inline sf::vec4 sf::vec4::operator/(const T& v) const {
    return vec4(xyzw[0] / v, xyzw[1] / v, xyzw[2] / v, xyzw[3] / v);
  }

  template <typename T>
  inline sf::vec4 sf::vec4::operator/=(const T& v) const {
    return *this / v;
  }

}
