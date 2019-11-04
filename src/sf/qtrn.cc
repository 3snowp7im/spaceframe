#include <sf/qtrn.h>

sf::qtrn sf::qtrn::from_axis_angle(const vec3<mpf>& v, const mpf& a) {
  const auto s = mpf::sin(a / 2);
  return qtrn(v[0] * s, v[1] * s, v[2] * s, mpf::cos(a / 2));
}

sf::qtrn::qtrn() {
}

sf::qtrn::qtrn(const mpf& x, const mpf& y, const mpf& z, const mpf& w) :
  xyzw({x, y, z, w}) {
}

sf::mpf sf::qtrn::length() const {
  return mpf::sqrt(xyzw[0] * xyzw[0] + xyzw[1] * xyzw[1] + xyzw[2] * xyzw[2] + xyzw[3] * xyzw[3]);
}

sf::qtrn sf::qtrn::unit() const {
  return *this / length();
}

sf::qtrn sf::qtrn::operator-() const {
  return qtrn(-xyzw[0], -xyzw[1], -xyzw[2], xyzw[3]);
}

sf::qtrn sf::qtrn::operator*(const qtrn& b) const {
  return qtrn(
    b[3] * xyzw[0] + b[0] * xyzw[3] - b[1] * xyzw[2] + b[2] * xyzw[1],
    b[3] * xyzw[1] + b[0] * xyzw[2] + b[1] * xyzw[3] - b[2] * xyzw[0],
    b[3] * xyzw[2] - b[0] * xyzw[1] + b[1] * xyzw[0] + b[2] * xyzw[3],
    b[3] * xyzw[3] - b[0] * xyzw[0] - b[1] * xyzw[1] - b[2] * xyzw[2]
  );
}

sf::vec3<sf::mpf> sf::qtrn::operator*(const vec3<mpf>& v) const {
  const vec3<mpf> u = {xyzw[0], xyzw[1], xyzw[2]};
  const auto uv = u * v;
  const auto uuv = u * uv;
  return v + ((uv * xyzw[3]) + uuv) * 2;
}

sf::mpf& sf::qtrn::operator[](size_t n) {
  return xyzw[n];
}

const sf::mpf& sf::qtrn::operator[](size_t n) const {
  return xyzw[n];
}
