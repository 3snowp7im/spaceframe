#include "tetra.h"

const sf::tetra::coord_t sf::tetra::coord_max = 0x7fffffffffffffffll;

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
  sf::vec3(sf::mpf(0), sf::mpf(0), sf::mpf(1)),
  sf::tetra::face_vertices[0] * sf::tetra::face_vertices[1],
  sf::tetra::face_vertices[2] * sf::tetra::face_vertices[0],
  sf::tetra::face_vertices[1] * sf::tetra::face_vertices[2],
};

sf::tetra::coords sf::tetra::point_to_coords(const vec3& v) const {
  const auto u = -orientation * v;
  return coords(
    static_cast<coord_t>(normals[0] ^ u),
    coord_max - static_cast<coord_t>(normals[1] ^ u),
    coord_max - static_cast<coord_t>(normals[2] ^ u),
    coord_max - static_cast<coord_t>(normals[3] ^ u)
  );
}

bool sf::tetra::is_point_in_bounds(const vec3& v) const {
  const auto u = -orientation * v;
  return (normals[1] ^ u) > 0 && (normals[2] ^ u) > 0 && (normals[3] ^ u) > 0;
}
