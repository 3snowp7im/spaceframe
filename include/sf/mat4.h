#pragma once

#include <array>
#include <sf/qtrn.h>
#include <sf/vec3.h>
#include <sf/vec4.h>

namespace sf {

  template <typename T>
  class mat4 {
    std::array<T, 16> m;
  public:
    static mat4<T> translate(const vec3<T>&);
    static mat4<T> rotate(const qtrn&);
    static mat4<T> project(const T&, const T&, const T&, const T&);
    mat4();
    mat4(const vec4<T>&, const vec4<T>&, const vec4<T>&, const vec4<T>&);
    mat4(
      const T&, const T&, const T&, const T&,
      const T&, const T&, const T&, const T&,
      const T&, const T&, const T&, const T&,
      const T&, const T&, const T&, const T&
    );
    mat4 norm() const;
    T& operator[](size_t n);
    const T& operator[](size_t n) const;
    mat4<T> operator/(const T&) const;
    mat4<T> operator/=(const T&) const;
    vec3<T> operator*(const vec3<T>&) const;
    vec4<T> operator*(const vec4<T>&) const;
    mat4<T> operator*(const mat4<T>&) const;
    template <typename U> operator std::array<U, 16>() const;
  };

  template <typename T>
  inline mat4<T>::mat4() {
  }

  template <typename T>
  inline mat4<T>::mat4(const vec4<T>& a, const vec4<T>& b, const vec4<T>& c, const vec4<T>& d) :
    m({
      a[0], b[0], c[0], d[0],
      a[1], b[1], c[1], d[1],
      a[2], b[2], c[2], d[2],
      a[3], b[3], c[3], d[3]
    }) {
  }

  template <typename T>
  inline mat4<T>::mat4(
    const T& a, const T& b, const T& c, const T& d,
    const T& e, const T& f, const T& g, const T& h,
    const T& i, const T& j, const T& k, const T& l,
    const T& m, const T& n, const T& o, const T& p
  ) :
    m({a, e, i, m, b, f, j, n, c, g, k, o, d, h, l, p}) {
  }

  template <typename T>
  inline T& mat4<T>::operator[](size_t n) {
    return m[n];
  }

  template <typename T>
  inline const T& mat4<T>::operator[](size_t n) const {
    return m[n];
  }

  template <typename T>
  inline mat4<T> mat4<T>::operator/(const T& v) const {
    return mat4<T>(
      m[0] / v, m[4] / v, m[8]  / v, m[12] / v,
      m[1] / v, m[5] / v, m[9]  / v, m[13] / v,
      m[2] / v, m[6] / v, m[10] / v, m[14] / v,
      m[3] / v, m[7] / v, m[11] / v, m[15] / v
    );
  }

  template <typename T>
  inline vec3<T> mat4<T>::operator*(const vec3<T>& v) const {
    return static_cast<vec3<T>>(*this * vec4<T>(v, T(0)));
  }

  template <typename T>
  inline vec4<T> mat4<T>::operator*(const vec4<T>& v) const {
    return vec4<T>(
      vec4<T>(m[0],  m[4],  m[8],  m[12]) ^ v,
      vec4<T>(m[1],  m[5],  m[9],  m[13]) ^ v,
      vec4<T>(m[2],  m[6],  m[10], m[14]) ^ v,
      vec4<T>(m[3],  m[7],  m[11], m[15]) ^ v
    );
  }

  template <typename T>
  inline mat4<T> mat4<T>::operator*(const mat4<T>& v) const {
    const auto a = *this * vec4<T>(v[0],  v[1],  v[2],  v[3]);
    const auto b = *this * vec4<T>(v[4],  v[5],  v[6],  v[7]);
    const auto c = *this * vec4<T>(v[8],  v[9],  v[10], v[11]);
    const auto d = *this * vec4<T>(v[12], v[13], v[14], v[15]);
    return mat4<T>(
      a[0], b[0], c[0], d[0],
      a[1], b[1], c[1], d[1],
      a[2], b[2], c[2], d[2],
      a[3], b[3], c[3], d[3]
    );
  }

  template <typename T>
  inline mat4<T> mat4<T>::norm() const {
    return *this / m[15];
  }

  template <typename T>
  inline mat4<T> mat4<T>::translate(const vec3<T>& v) {
    return mat4<T>(
      T(1), T(0), T(0), v[0],
      T(0), T(1), T(0), v[1],
      T(0), T(0), T(1), v[2],
      T(0), T(0), T(0), T(1)
    );
  }

  template <typename T>
  inline mat4<T> mat4<T>::rotate(const qtrn& v) {
    const auto q = v.unit();
    return mat4<T>(
       q[3],  q[2], -q[1],  q[0],
      -q[2],  q[3],  q[0],  q[1],
       q[1], -q[0],  q[3],  q[2],
      -q[0], -q[1], -q[2],  q[3]
    ) * mat4(
       q[3],  q[2], -q[1], -q[0],
      -q[2],  q[3],  q[0], -q[1],
       q[1], -q[0],  q[3], -q[2],
       q[0],  q[1],  q[2],  q[3]
    );
  }

  template <typename T>
  inline mat4<T> mat4<T>::project(const T& fov, const T& aspect, const T& near, const T& far) {
    const auto scale = T::tan(fov / 2);
    return mat4<T>(
      1 / (aspect * scale), T(0), T(0), T(0),
      T(0), 1 / scale, T(0), T(0),
      T(0), T(0), -(far + near) / (far - near), -(2 * far * near) / (far - near),
      T(0), T(0), T(-1), T(0)
    );
  }

  template <typename T>
  template <typename U>
  inline mat4<T>::operator std::array<U, 16>() const {
    std::array<U, 16> array;
    for (int i = 0; i < m.size(); i++) {
      array[i] = static_cast<U>(m[i]);
    }
    return array;
  }

}
