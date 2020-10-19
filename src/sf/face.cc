#include <sf/face.h>
#include <cmath>

const sf::face::coord_t sf::face::coord_max = (~0lu >> 3) + 1;

const unsigned sf::face::coord_max_log2 = std::log2(sf::face::coord_max);

std::array<sf::vec3<sf::mpf>, 3> sf::face::vertices;

static std::array<sf::vec3<sf::mpf>, 4> normals;

static sf::mpf height;

static sf::mpf radius;

void sf::face::init() {
  const auto x = 2 / mpf::sqrt(10 + 2 * mpf::sqrt(5));
  const auto h = mpf::sqrt(6 / (5 + mpf::sqrt(5)));
  const auto y = mpf::sqrt(2 * (5 - mpf::sqrt(5)) / 15);
  const auto z = mpf::sqrt((5 + 2 * mpf::sqrt(5)) / 15);
  face::vertices = {{
    vec3<mpf>(0, y, z).unit(),
    vec3<mpf>( x, -h + y, z).unit(),
    vec3<mpf>(-x, -h + y, z).unit(),
  }};
  normals = {
    (vertices[2] * vertices[1]).unit(),
    (vertices[0] * vertices[2]).unit(),
    (vertices[1] * vertices[0]).unit(),
    {0, 0, 1},
  };
  radius = mpf::sqrt(15 - 6 * mpf::sqrt(5));
  height = mpf::sqrt((5 + mpf::sqrt(5)) / 10);
}

sf::face::face() {
}

sf::face::face(const qtrn& orientation) :
  orientation(orientation) {
}

sf::face& sf::face::operator=(const face& v) {
  orientation = v.orientation;
  return *this;
}

bool sf::face::is_point_in_bounds(const vec3<mpf>& p) const {
  const auto u = -orientation * p;
  return (normals[0] ^ u) >= 0 && (normals[1] ^ u) >= 0 && (normals[2] ^ u) >= 0 && (normals[3] ^ u) >= 0;
}

sf::vec3<sf::mpf> sf::face::face_pos_from_point(const vec3<mpf>& p) const {
  static const auto a = sf::mpf::sqrt((5 + 2 * sf::mpf::sqrt(5)) / 15);
  // Get the length of the vector.
  const auto m = p.length();
  if (m == 0) {
    return vec3<mpf>(0, 0, 0);
  }
  // Normalize the dot product of the z axis and the vector.
  const auto t = (vec3<mpf>(0, 0, 1) ^ (-orientation * p)) / m;
  // Calculate the slope of the vector.
  const auto s = mpf::sqrt(1 - t * t) / t;
  // Calculate the point where the vector intercepts the plane.
  const auto x = m * a;
  const auto y = s * x;
  // Scale the vector.
  return p * mpf::sqrt(x * x + y * y) / m;
}

sf::face::vec_t sf::face::vec_from_face_pos(const vec3<mpf>& v) const {
  const auto u = -orientation * v;
  return vec_t(
    coord_max - (normals[0] ^ u) / height,
    coord_max - (normals[1] ^ u) / height,
    coord_max - (normals[2] ^ u) / height,
    (normals[3] ^ u) * radius
  );
}

sf::face::coords_t sf::face::coords_from_vec(const vec_t& vec) {
  return coords_t(mpf::round(vec[0]), mpf::round(vec[1]), mpf::round(vec[2]), mpf::round(vec[3]));
}

static sf::vec3<sf::mpf> solve(const sf::vec4<sf::mpf>& a, const sf::vec4<sf::mpf>& b, const sf::vec4<sf::mpf>& c) {
  const sf::mpf det =   a[0] * (b[1] * c[2] - c[1] * b[2])
                      - a[1] * (b[0] * c[2] - b[2] * c[0])
                      + a[2] * (b[0] * c[1] - b[1] * c[0]);
  if (det == 0) {
    throw std::runtime_error("No solution exists for system");
  }
  const sf::vec3<sf::mpf> i0 = {
    (b[1] * c[2] - c[1] * b[2]) / det,
    (a[2] * c[1] - a[1] * c[2]) / det,
    (a[1] * b[2] - a[2] * b[1]) / det,
  };
  const sf::vec3<sf::mpf> i1 = {
    (b[2] * c[0] - b[0] * c[2]) / det,
    (a[0] * c[2] - a[2] * c[0]) / det,
    (b[0] * a[2] - a[0] * b[2]) / det,
  };
  const sf::vec3<sf::mpf> i2 = {
    (b[0] * c[1] - c[0] * b[1]) / det,
    (c[0] * a[1] - a[0] * c[1]) / det,
    (a[0] * b[1] - b[0] * a[1]) / det,
  };
  const sf::vec3<sf::mpf> d(-a[3], -b[3], -c[3]);
  return sf::vec3<sf::mpf>(i0 ^ d, i1 ^ d, i2 ^ d);
}

sf::vec3<sf::mpf> sf::face::point_from_vert(const vec3<coord_t>& vert) {
  auto vec = static_cast<vec3<mpf>>(vert);
  const vec4<mpf> a(normals[2], -(coord_max - vec[1]) * height);
  const vec4<mpf> c(normals[0], -(coord_max - vec[0]) * height);
  const vec4<mpf> d(normals[3], -vec[2] / radius);
  const auto s = solve(a, c, d);
  return s * (vec[2] / s.length());
}
