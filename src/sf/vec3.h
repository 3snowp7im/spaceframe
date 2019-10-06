#pragma once

#include <array>
#include "mpf.h"

namespace sf {

  class vec3 {
    std::array<mpf, 3> xyz;
  public:
    vec3();
    vec3(const mpf&, const mpf&, const mpf&);
    std::array<mpf, 3>::iterator begin();
    std::array<mpf, 3>::const_iterator begin() const;
    std::array<mpf, 3>::iterator end();
    std::array<mpf, 3>::const_iterator end() const;
    size_t size() const;
    mpf length() const;
    vec3 unit() const;
    void unitize();
    vec3 operator-() const;
    vec3 operator+(const vec3&) const;
    vec3 operator-(const vec3&) const;
    vec3 operator*(const vec3&) const;
    mpf operator^(const vec3&) const;
    mpf& operator[](size_t n);
    const mpf& operator[](size_t n) const;
    template <typename T> operator std::array<T, 3>() const;
    template <typename T> vec3 operator*(const T&) const;
    template <typename T> vec3 operator/(const T&) const;
    template <typename T> vec3 operator/=(const T&) const;
    template <typename T> friend vec3 operator*(int, const vec3&);
  };

  inline vec3::vec3() {
  }

  inline vec3::vec3(const mpf& x, const mpf& y, const mpf& z)
    : xyz({x, y, z})
  {
  }

  template <typename T>
  inline vec3::operator std::array<T, 3>() const {
    return std::array<T, 3>({
      static_cast<T>(xyz[0]),
      static_cast<T>(xyz[1]),
      static_cast<T>(xyz[2]),
    });
  }

  template <typename T>
  inline sf::vec3 sf::vec3::operator*(const T& v) const {
    return vec3(xyz[0] * v, xyz[1] * v, xyz[2] * v);
  }

  template <typename T>
  inline sf::vec3 sf::vec3::operator/(const T& v) const {
    return vec3(xyz[0] / v, xyz[1] / v, xyz[2] / v);
  }

  template <typename T>
  inline sf::vec3 sf::vec3::operator/=(const T& v) const {
    return *this / v;
  }

  template <typename T>
  inline vec3 operator*(T a, const vec3& b) {
    return vec3(a * b.xyz[0], a * b.xyz[1], a * b.xyz[2]);
  }

}
