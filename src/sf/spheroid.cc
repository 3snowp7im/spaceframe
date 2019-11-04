#include <sf/spheroid.h>

std::array<sf::face, 20> sf::spheroid::face_array;

constexpr sf::spheroid::face_access sf::spheroid::faces;

void sf::spheroid::init() {
  face_array = {
    sf::face(sf::qtrn(0, 0, 0, 1)),
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::face(
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
    sf::face(
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
    sf::face(
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
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::face(
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
    sf::face(
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
    sf::face(
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
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      )
    ),
    sf::face(sf::qtrn(sf::mpf(-1), 0, 0, 0)),
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::face(
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
    sf::face(
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
    sf::face(
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
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
    sf::face(
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
    sf::face(
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
    sf::face(
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
    sf::face(
      sf::qtrn(0, 0, sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
        sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
        0,
        0,
        sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
      ) * sf::qtrn(sf::mpf(-1), 0, 0, 0)
    ),
  };
}

const sf::face& sf::spheroid::face_access::operator[](size_t i) const {
  return sf::spheroid::face_array[i];
}

std::array<sf::face, 20>::const_iterator sf::spheroid::face_access::begin() const {
  return sf::spheroid::face_array.begin();
}

std::array<sf::face, 20>::const_iterator sf::spheroid::face_access::end() const {
  return sf::spheroid::face_array.end();
}

sf::vec3<sf::mpf> sf::spheroid::face_pos_from_point(const vec3<mpf>& p) {
  for (const auto& face : faces) {
    if (face.is_point_in_bounds(p)) {
      return face.face_pos_from_point(p);
    }
  }
  throw std::runtime_error("Vertex not in any face");
}
