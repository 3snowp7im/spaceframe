#pragma once

#include <array>

namespace sf {

  template <typename T>
  class vec3 {
    std::array<T, 3> xyz;
  public:
    static const vec3<T> zero;
    vec3();
    vec3(const T&, const T&, const T&);
    typename std::array<T, 3>::iterator begin();
    typename std::array<T, 3>::const_iterator begin() const;
    typename std::array<T, 3>::iterator end();
    typename std::array<T, 3>::const_iterator end() const;
    size_t size() const;
    T length() const;
    vec3<T> unit() const;
    void unitize();
    vec3<T> operator-() const;
    vec3<T> operator+(const vec3<T>&) const;
    vec3<T> operator-(const vec3<T>&) const;
    vec3<T> operator*(const vec3<T>&) const;
    T operator^(const vec3<T>&) const;
    T& operator[](size_t n);
    const T& operator[](size_t n) const;
    bool operator==(const vec3<T>&) const;
    template <typename U> operator vec3<U>() const;
    template <typename U> operator std::array<U, 3>() const;
    template <typename U> vec3<T> operator+(const U&) const;
    template <typename U> vec3<T> operator-(const U&) const;
    template <typename U> vec3<T> operator*(const U&) const;
    template <typename U> vec3<T> operator/(const U&) const;
    template <typename U> vec3<T> operator+=(const U&);
    template <typename U> vec3<T> operator-=(const U&);
    template <typename U> vec3<T> operator*=(const U&);
    template <typename U> vec3<T> operator/=(const U&);
    template <typename U, typename V> friend vec3<U> operator*(const V&, const vec3<U>&);
  };

  template <typename T>
  inline vec3<T>::vec3() {
  }

  template <typename T>
  inline vec3<T>::vec3(const T& x, const T& y, const T& z) :
    xyz({x, y, z}) {
  }

  template <typename T>
  inline typename std::array<T, 3>::iterator vec3<T>::begin() {
    return xyz.begin();
  }

  template <typename T>
  inline typename std::array<T, 3>::const_iterator vec3<T>::begin() const {
    return xyz.begin();
  }

  template <typename T>
  inline typename std::array<T, 3>::iterator vec3<T>::end() {
    return xyz.end();
  }

  template <typename T>
  inline typename std::array<T, 3>::const_iterator vec3<T>::end() const {
    return xyz.end();
  }

  template <typename T>
  inline size_t vec3<T>::size() const {
    return 3;
  }

  template <typename T>
  inline T vec3<T>::length() const {
    return T::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
  }

  template <typename T>
  inline vec3<T> vec3<T>::unit() const {
    return *this / length();
  }

  template <typename T>
  inline void vec3<T>::unitize() {
    *this /= length();
  }

  template <typename T>
  inline vec3<T> vec3<T>::operator-() const {
    return vec3<T>(-xyz[0], -xyz[1], -xyz[2]);
  }

  template <typename T>
  inline vec3<T> vec3<T>::operator+(const vec3<T>& v) const {
    return vec3<T>(xyz[0] + v[0], xyz[1] + v[1], xyz[2] + v[2]);
  }

  template <typename T>
  inline vec3<T> vec3<T>::operator-(const vec3<T>& v) const {
    return vec3<T>(xyz[0] - v[0], xyz[1] - v[1], xyz[2] - v[2]);
  }

  template <typename T>
  inline vec3<T> vec3<T>::operator*(const vec3<T>& v) const {
    return vec3<T>(
      xyz[1] * v[2] - xyz[2] * v[1],
      xyz[2] * v[0] - xyz[0] * v[2],
      xyz[0] * v[1] - xyz[1] * v[0]
    );
  }

  template <typename T>
  inline T vec3<T>::operator^(const vec3<T>& v) const {
    return xyz[0] * v[0] + xyz[1] * v[1] + xyz[2] * v[2];
  }

  template <typename T>
  inline T& vec3<T>::operator[](size_t n) {
    return xyz[n];
  }

  template <typename T>
  inline const T& vec3<T>::operator[](size_t n) const {
    return xyz[n];
  }

  template <typename T>
  inline bool vec3<T>::operator==(const vec3<T>& v) const {
    return xyz[0] == v[0] && xyz[1] == v[1] && v[2] == xyz[2];
  }

  template <typename T>
  template <typename U>
  inline vec3<T>::operator vec3<U>() const {
    return vec3<U>(U(xyz[0]), U(xyz[1]), U(xyz[2]));
  }

  template <typename T>
  template <typename U>
  inline vec3<T>::operator std::array<U, 3>() const {
    return std::array<U, 3>({
      static_cast<U>(xyz[0]),
      static_cast<U>(xyz[1]),
      static_cast<U>(xyz[2]),
    });
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator+(const U& v) const {
    return vec3<T>(xyz[0] + v, xyz[1] + v, xyz[2] + v);
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator-(const U& v) const {
    return vec3<T>(xyz[0] - v, xyz[1] - v, xyz[2] - v);
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator*(const U& v) const {
    return vec3<T>(xyz[0] * v, xyz[1] * v, xyz[2] * v);
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator/(const U& v) const {
    return vec3(xyz[0] / v, xyz[1] / v, xyz[2] / v);
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator+=(const U& v) {
    xyz = (*this + v).xyz;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator-=(const U& v) {
    xyz = (*this - v).xyz;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator*=(const U& v) {
    xyz = (*this * v).xyz;
    return *this;
  }

  template <typename T>
  template <typename U>
  inline vec3<T> vec3<T>::operator/=(const U& v) {
    xyz = (*this / v).xyz;
    return *this;
  }

  template <typename U, typename V>
  inline vec3<U> operator*(const V& a, const vec3<U>& b) {
    return vec3<U>(a * b.xyz[0], a * b.xyz[1], a * b.xyz[2]);
  }

}

namespace std {

  template <typename T>
  inline string to_string(const sf::vec3<T>& v) {
    return "<" + to_string(v[0]) + ", " + to_string(v[1]) + ", " + to_string(v[2]) + ">";
  }

}
