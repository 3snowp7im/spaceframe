#pragma once

#include <array>
#include <string>
#include "vec3.h"

namespace sf {

  template <typename T>
  class vec4 {
    std::array<T, 4> xyzw;
  public:
    static vec4<T> from_vertex_normal(const vec3<T>&, const vec3<T>&);
    vec4();
    vec4(const T&);
    vec4(const T&, const T&, const T&, const T&);
    vec4(const vec3<T>&, const T& = T(1));
    typename std::array<T, 4>::iterator begin();
    typename std::array<T, 4>::const_iterator begin() const;
    typename std::array<T, 4>::iterator end();
    typename std::array<T, 4>::const_iterator end() const;
    size_t size() const;
    T length() const;
    vec4<T> unit() const;
    void unitize();
    vec4<T> operator-() const;
    vec4<T> operator+(const vec4<T>&) const;
    vec4<T> operator-(const vec4<T>&) const;
    T operator^(const vec4<T>&) const;
    operator vec3<T>() const;
    T& operator[](size_t n);
    const T& operator[](size_t n) const;
    template <typename U> operator vec4<U>() const;
    template <typename U> operator std::array<U, 4>() const;
    template <typename U> vec4<T> operator+(const U&) const;
    template <typename U> vec4<T> operator-(const U&) const;
    template <typename U> vec4<T> operator*(const U&) const;
    template <typename U> vec4<T> operator/(const U&) const;
    template <typename U> vec4<T> operator+=(const U&);
    template <typename U> vec4<T> operator-=(const U&);
    template <typename U> vec4<T> operator*=(const U&);
    template <typename U> vec4<T> operator/=(const U&);
  };

  template <typename T>
  inline vec4<T> vec4<T>::from_vertex_normal(const vec3<T>& v, const vec3<T>& n) {
    return sf::vec4<sf::mpf>(n, -(n ^ v));
  }

  template <typename T>
  inline vec4<T>::vec4() :
    xyzw({0, 0, 0, 0}) {
  }

  template <typename T>
  inline vec4<T>::vec4(const T& v) :
    xyzw({v, v, v, v}) {
  }

  template <typename T>
  inline vec4<T>::vec4(const T& x, const T& y, const T& z, const T& w) :
    xyzw({x, y, z, w}) {
  }

  template <typename T>
  inline vec4<T>::vec4(const vec3<T>& xyz, const T& w) :
    xyzw({xyz[0], xyz[1], xyz[2], w}) {
  }

  template <typename T>
  inline typename std::array<T, 4>::iterator vec4<T>::begin() {
    return xyzw.begin();
  }

  template <typename T>
  inline typename std::array<T, 4>::const_iterator vec4<T>::begin() const {
    return xyzw.begin();
  }

  template <typename T>
  inline typename std::array<T, 4>::iterator vec4<T>::end() {
    return xyzw.end();
  }

  template <typename T>
  inline typename std::array<T, 4>::const_iterator vec4<T>::end() const {
    return xyzw.end();
  }

  template <typename T>
  inline size_t vec4<T>::size() const {
    return 4;
  }

  template <typename T>
  inline T vec4<T>::length() const {
    return T::sqrt(xyzw[0] * xyzw[0] + xyzw[1] * xyzw[1] + xyzw[2] * xyzw[2] + xyzw[3] * xyzw[3]);
  }

  template <typename T>
  inline vec4<T> vec4<T>::unit() const {
    return *this / length();
  }

  template <typename T>
  inline void vec4<T>::unitize() {
    *this /= length();
  }

  template <typename T>
  inline vec4<T> vec4<T>::operator-() const {
    return vec4<T>(-xyzw[0], -xyzw[1], -xyzw[2], -xyzw[3]);
  }

  template <typename T>
  inline vec4<T> vec4<T>::operator+(const vec4<T>& v) const {
    return vec4<T>(xyzw[0] + v[0], xyzw[1] + v[1], xyzw[2] + v[2], xyzw[3] + v[3]);
  }

  template <typename T>
  vec4<T> vec4<T>::operator-(const vec4<T>& v) const {
    return vec4<T>(xyzw[0] - v[0], xyzw[1] - v[1], xyzw[2] - v[2], xyzw[3] - v[3]);
  }

  template <typename T>
  inline T vec4<T>::operator^(const vec4<T>& v) const {
    return xyzw[0] * v[0] + xyzw[1] * v[1] + xyzw[2] * v[2] + xyzw[3] * v[3];
  }

  template <typename T>
  inline vec4<T>::operator vec3<T>() const {
    return vec3<T>(xyzw[0], xyzw[1], xyzw[2]);
  }

  template <typename T>
  inline T& vec4<T>::operator[](size_t n) {
    return xyzw[n];
  }

  template <typename T>
  inline const T& vec4<T>::operator[](size_t n) const {
    return xyzw[n];
  }

  template <typename T>
  template <typename U>
  inline vec4<T>::operator vec4<U>() const {
    return vec4<U>(
      static_cast<U>(xyzw[0]),
      static_cast<U>(xyzw[1]),
      static_cast<U>(xyzw[2]),
      static_cast<U>(xyzw[3])
    );
  }

  template <typename T>
  template <typename U>
  inline vec4<T>::operator std::array<U, 4>() const {
    return std::array<U, 4>({
      static_cast<U>(xyzw[0]),
      static_cast<U>(xyzw[1]),
      static_cast<U>(xyzw[2]),
      static_cast<U>(xyzw[3]),
    });
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator+(const U& v) const {
    return vec4(xyzw[0] + v, xyzw[1] + v, xyzw[2] + v, xyzw[3] + v);
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator-(const U& v) const {
    return vec4<T>(xyzw[0] - v, xyzw[1] - v, xyzw[2] - v, xyzw[3] - v);
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator*(const U& v) const {
    return vec4<T>(xyzw[0] * v, xyzw[1] * v, xyzw[2] * v, xyzw[3] * v);
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator/(const U& v) const {
    return vec4<T>(xyzw[0] / v, xyzw[1] / v, xyzw[2] / v, xyzw[3] / v);
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator+=(const U& v) {
    xyzw = (*this + v).xyzw;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator-=(const U& v) {
    xyzw = (*this - v).xyzw;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator*=(const U& v) {
    xyzw = (*this * v).xyzw;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec4<T> vec4<T>::operator/=(const U& v) {
    xyzw = (*this / v).xyzw;
    return *this;
  }

}

namespace std {

  template <typename T>
  inline string to_string(const sf::vec4<T>& v) {
    return "<" + to_string(v[0]) + ", " + to_string(v[1]) + ", " + to_string(v[2]) + ", " + to_string(v[3]) + ">";
  }

}
