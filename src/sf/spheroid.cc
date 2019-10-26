#include "spheroid.h"

std::array<sf::tetra, 20> sf::spheroid::tetra_array;

void sf::spheroid::init() {
  tetra_array = {
    sf::tetra(sf::qtrn(0, 0, 0, 1)),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::tetra(sf::qtrn(sf::mpf(-1), 0, 0, 0)),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::tetra(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
  };
}

bool sf::spheroid::tetra_access::constructed = false;

sf::spheroid::tetra_access::tetra_access() {
  if (constructed) {
    throw std::runtime_error("Duplicate sf::spheroid::tetra_access instance constructed");
  }
  constructed = true;
}

const sf::tetra& sf::spheroid::tetra_access::operator[](size_t i) const {
  return sf::spheroid::tetra_array[i];
}

std::array<sf::tetra, 20>::const_iterator sf::spheroid::tetra_access::begin() const {
  return sf::spheroid::tetra_array.begin();
}

std::array<sf::tetra, 20>::const_iterator sf::spheroid::tetra_access::end() const {
  return sf::spheroid::tetra_array.end();
}

sf::spheroid::spheroid(tetra::coord_t r) :
  r(r) {
}

const sf::spheroid::tetra_access sf::spheroid::tetras;

sf::vec3<sf::mpf> sf::spheroid::vertex_to_tetra_space(const vec3<mpf>& v) {
  static const auto a = sf::mpf::sqrt((5 + 2 * sf::mpf::sqrt(5)) / 15);
  for (const auto& tetra : tetras) {
    if (tetra.is_vertex_in_bounds(v)) {
      // Get the length of the vector.
      const auto m = v.length();
      if (m == 0) {
        return vec3<mpf>(0, 0, 0);
      }
      // Normalize the dot product of the z axis and the vector.
      const auto t = (vec3<mpf>(0, 0, 1) ^ (-tetra.orientation * v)) / m;
      // Calculate the slope of the vector.
      const auto s = mpf::sqrt(1 - t * t) / t;
      // Calculate the point where the vector intercepts the plane.
      const auto x = m * a;
      const auto y = s * x;
      // Scale the vector.
      return v * mpf::sqrt(x * x + y * y) / m;
    }
  }
  throw std::runtime_error("Vertex not in any tetra space");
}
