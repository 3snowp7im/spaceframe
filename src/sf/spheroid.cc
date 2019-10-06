#include "spheroid.h"

const std::array<sf::tetra, 20> sf::spheroid::tetras = {
  sf::tetra(sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf(0), sf::mpf(1))),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    )
  ),
  sf::tetra(sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      -sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::cos(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf::sin(sf::mpf::pi() / 3) * sf::mpf::sin((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() - sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  ),
  sf::tetra(
    sf::qtrn(sf::mpf(0), sf::mpf(0), sf::mpf::sin(sf::mpf::pi() / 2), sf::mpf::cos(sf::mpf::pi() / 2)) * sf::qtrn(
      sf::mpf::sin((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2),
      sf::mpf(0),
      sf::mpf(0),
      sf::mpf::cos((sf::mpf::pi() + sf::mpf::acos(-sf::mpf::sqrt(5) / 3)) / 2)
    ) * sf::qtrn(sf::mpf(-1), sf::mpf(0), sf::mpf(0), sf::mpf(0))
  )
};

static const auto a = sf::mpf::sqrt((5 + 2 * sf::mpf::sqrt(5)) / 15);

sf::vec3 sf::spheroid::point_to_tetra_space(const vec3& v) {
  for (const auto& tetra : spheroid::tetras) {
    if (tetra.is_point_in_bounds(v)) {
      // Calculate the dot product of the vector and itself.
      const auto c = v ^ v;
      // The length is the square root of the dot product.
      const auto m = mpf::sqrt(c);
      // Calculate the normalized dot product of the z axis and the vector.
      const auto t = (vec3(mpf(0), mpf(0), mpf(1)) ^ (-tetra.orientation * v)) / m;
      // Calculate the slope of the vector.
      const auto s = mpf::sqrt(1 - t * t) / t;
      // Now the point that intercepts the face can be calculated.
      const auto x = m * a;
      const auto y = s * x;
      // The vector can be scaled using the factor ||p||^2 / ||v||^2.
      return v * (x * x + y * y) / c;
    }
  }
  throw std::runtime_error("Point not in any tetra space");
}
