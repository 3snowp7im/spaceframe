#include "tetra.h"

bool sf::tetra::vertex_access::constructed = false;

sf::tetra::vertex_access::vertex_access() {
  if (constructed) {
    throw std::runtime_error("Duplicate sf::tetra::vertex_access instance constructed");
  }
  constructed = true;
}

const sf::tetra::coord_t sf::tetra::coord_max = static_cast<long>((~0lu >> 3) + 1);

std::array<sf::vec3<sf::mpf>, 3> sf::tetra::vertex_array;

static std::array<sf::vec3<sf::mpf>, 4> normals;

void sf::tetra::init() {
  const auto x = 2 / mpf::sqrt(10 + 2 * mpf::sqrt(5));
  const auto h = mpf::sqrt(6 / (5 + mpf::sqrt(5)));
  const auto y = mpf::sqrt(2 * (5 - mpf::sqrt(5)) / 15);
  const auto z = mpf::sqrt((5 + 2 * mpf::sqrt(5)) / 15);
  tetra::vertex_array = {{
    vec3<sf::mpf>(0, y, z).unit(),
    vec3<sf::mpf>( x, -h + y, z).unit(),
    vec3<sf::mpf>(-x, -h + y, z).unit(),
  }};
  normals = {
    (sf::tetra::vertices[2] * sf::tetra::vertices[1]).unit(),
    (sf::tetra::vertices[0] * sf::tetra::vertices[2]).unit(),
    (sf::tetra::vertices[1] * sf::tetra::vertices[0]).unit(),
    {0, 0, 1},
  };
}

const sf::tetra::vertex_access sf::tetra::vertices;

const sf::vec3<sf::mpf>& sf::tetra::vertex_access::operator[](size_t i) const {
  return sf::tetra::vertex_array[i];
}

sf::tetra::tetra() {
}

sf::tetra::tetra(const qtrn& orientation) :
  orientation(orientation) {
}

sf::tetra& sf::tetra::operator=(const tetra& v) {
  orientation = v.orientation;
}

bool sf::tetra::is_vertex_in_bounds(const vec3<mpf>& v) const {
  const auto u = -orientation * v;
  return (normals[0] ^ u) >= 0 && (normals[1] ^ u) >= 0 && (normals[2] ^ u) >= 0 && (normals[3] ^ u) >= 0;
}

sf::tetra::vec_t sf::tetra::vec_from_vertex(const vec3<mpf>& v) const {
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

