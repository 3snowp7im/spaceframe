#include <sf/face.h>

const sf::face::coord_t sf::face::coord_max = static_cast<long>((~0lu >> 3) + 1);

std::array<sf::vec3<sf::mpf>, 3> sf::face::vert_array;

constexpr sf::face::vert_access sf::face::verts;

static std::array<sf::vec3<sf::mpf>, 4> normals;

void sf::face::init() {
  const auto x = 2 / mpf::sqrt(10 + 2 * mpf::sqrt(5));
  const auto h = mpf::sqrt(6 / (5 + mpf::sqrt(5)));
  const auto y = mpf::sqrt(2 * (5 - mpf::sqrt(5)) / 15);
  const auto z = mpf::sqrt((5 + 2 * mpf::sqrt(5)) / 15);
  face::vert_array = {{
    vec3<sf::mpf>(0, y, z).unit(),
    vec3<sf::mpf>( x, -h + y, z).unit(),
    vec3<sf::mpf>(-x, -h + y, z).unit(),
  }};
  normals = {
    (sf::face::vert_array[2] * sf::face::vert_array[1]).unit(),
    (sf::face::vert_array[0] * sf::face::vert_array[2]).unit(),
    (sf::face::vert_array[1] * sf::face::vert_array[0]).unit(),
    {0, 0, 1},
  };
}

const sf::vec3<sf::mpf>& sf::face::vert_access::operator[](size_t i) const {
  return sf::face::vert_array[i];
}

sf::face::face() {
}

sf::face::face(const qtrn& orientation) :
  orientation(orientation) {
}

sf::face& sf::face::operator=(const face& v) {
  orientation = v.orientation;
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
  static const auto radius = sf::mpf::sqrt(15 - 6 * sf::mpf::sqrt(5));
  static const auto height = sf::mpf::sqrt((5 + sf::mpf::sqrt(5)) / 10);
  const auto u = -orientation * v;
  return vec_t(
    coord_max - (normals[0] ^ u) / height,
    coord_max - (normals[1] ^ u) / height,
    coord_max - (normals[2] ^ u) / height,
    (normals[3] ^ u) * radius
  );
}
