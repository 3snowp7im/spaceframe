#include "tetra.h"

sf::tetra::tetra(const qtrn& orientation)
  : orientation(orientation)
{
}

static const auto a =  2 / sf::mpf::sqrt(10 + 2 * sf::mpf::sqrt(5));
static const auto b = -2 / sf::mpf::sqrt(3 * (10 + 2 * sf::mpf::sqrt(5)));
static const auto z = sf::mpf::sqrt((5 + 2 * sf::mpf::sqrt(5)) / 15);

const std::array<sf::vec3, 3> sf::tetra::face_vertices = {
  sf::vec3(-a, b, z),
  sf::vec3( a, b, z),
  sf::vec3(sf::mpf(0), sf::mpf::sqrt(2 * (5 - mpf::sqrt(5)) / 15), z),
};

static const std::array<sf::vec3, 4> normals = {
  sf::tetra::face_vertices[0] * sf::tetra::face_vertices[1],
  sf::tetra::face_vertices[2] * sf::tetra::face_vertices[0],
  sf::tetra::face_vertices[1] * sf::tetra::face_vertices[2],
  sf::vec3(sf::mpf(0), sf::mpf(0), sf::mpf(1)),
};

sf::tetra::coords sf::tetra::point_to_coords(const vec3& v) const {
  const auto u = -orientation * v;
  return coords(normals[0] ^ u, normals[1] ^ u, normals[2] ^ u, normals[3] ^ u);
}

bool sf::tetra::is_point_in_bounds(const vec3& v) const {
  const auto u = -orientation * v;
  return (normals[0] ^ u) > 0 && (normals[1] ^ u) > 0 && (normals[2] ^ u) > 0;
}
