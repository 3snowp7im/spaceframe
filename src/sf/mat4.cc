#include <stdexcept>
#include "mat4.h"

sf::mat4::mat4() {
}

sf::mat4::mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d)
  : m({
      a[0], b[0], c[0], d[0],
      a[1], b[1], c[1], d[1],
      a[2], b[2], c[2], d[2],
      a[3], b[3], c[3], d[3]
    })
{
}

sf::mat4::mat4(
  const mpf& a, const mpf& b, const mpf& c, const mpf& d,
  const mpf& e, const mpf& f, const mpf& g, const mpf& h,
  const mpf& i, const mpf& j, const mpf& k, const mpf& l,
  const mpf& m, const mpf& n, const mpf& o, const mpf& p
) : m({a, e, i, m, b, f, j, n, c, g, k, o, d, h, l, p})
{
}

sf::mpf& sf::mat4::operator[](size_t n) {
  return m[n];
}

const sf::mpf& sf::mat4::operator[](size_t n) const {
  return m[n];
}

sf::mat4 sf::mat4::operator/(const mpf& v) const {
  return mat4(
    m[0] / v, m[4] / v, m[8]  / v, m[12] / v,
    m[1] / v, m[5] / v, m[9]  / v, m[13] / v,
    m[2] / v, m[6] / v, m[10] / v, m[14] / v,
    m[3] / v, m[7] / v, m[11] / v, m[15] / v
  );
}

sf::vec3 sf::mat4::operator*(const vec3& v) const {
  return static_cast<vec3>(*this * vec4(v, mpf(0)));
}

sf::vec4 sf::mat4::operator*(const vec4& v) const {
  return vec4(
    m[0] * v[0] + m[4] * v[1] + m[8]  * v[2] + m[12] * v[3],
    m[1] * v[0] + m[5] * v[1] + m[9]  * v[2] + m[13] * v[3],
    m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3],
    m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3]
  );
}

sf::mat4 sf::mat4::operator*(const mat4& v) const {
  const auto a = *this * vec4(v[0],  v[1],  v[2],  v[3]);
  const auto b = *this * vec4(v[4],  v[5],  v[6],  v[7]);
  const auto c = *this * vec4(v[8],  v[9],  v[10], v[11]);
  const auto d = *this * vec4(v[12], v[13], v[14], v[15]);
  return mat4(
    a[0], b[0], c[0], d[0],
    a[1], b[1], c[1], d[1],
    a[2], b[2], c[2], d[2],
    a[3], b[3], c[3], d[3]
  );
}

sf::mat4 sf::mat4::norm() const {
  return *this / m[15];
}

sf::mat4 sf::mat4::translate(const vec3& v) {
  return mat4(
    mpf(1), mpf(0), mpf(0), v[0],
    mpf(0), mpf(1), mpf(0), v[1],
    mpf(0), mpf(0), mpf(1), v[2],
    mpf(0), mpf(0), mpf(0), mpf(1)
  );
}

sf::mat4 sf::mat4::rotate(const qtrn& v) {
  const auto q = v.unit();
  return mat4(
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

sf::mat4 sf::mat4::project(const mpf& fov, const mpf& aspect, const mpf& near, const mpf& far) {
  const auto scale = mpf::tan(fov / 2);
  return mat4(
    1 / (aspect * scale), mpf(0), mpf(0), mpf(0),
    mpf(0), 1 / scale, mpf(0), mpf(0),
    mpf(0), mpf(0), -(far + near) / (far - near), -(2 * far * near) / (far - near),
    mpf(0), mpf(0), mpf(-1), mpf(0)
  );
}

const sf::mat4 sf::mat4::identity = mat4(
  mpf(1), mpf(0), mpf(0), mpf(0),
  mpf(0), mpf(1), mpf(0), mpf(0),
  mpf(0), mpf(0), mpf(1), mpf(0),
  mpf(0), mpf(0), mpf(0), mpf(1)
);
