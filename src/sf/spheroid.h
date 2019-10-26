#pragma once

#include <array>
#include <sf/sf.h>
#include "mpf.h"
#include "tetra.h"
#include "vec3.h"

namespace sf {

  class spheroid {
    static void init();
    static std::array<tetra, 20> tetra_array;
  public:
    static const class tetra_access {
      static bool constructed;
    public:
      tetra_access();
      const tetra& operator[](size_t) const;
      std::array<tetra, 20>::const_iterator begin() const;
      std::array<tetra, 20>::const_iterator end() const;
    } tetras;
    static sf::vec3<sf::mpf> vertex_to_tetra_space(const vec3<mpf>&);
    spheroid(tetra::coord_t);
    const tetra::coord_t r;
    friend void sf::init();
    friend const tetra& tetra_access::operator[](size_t i) const;
    friend std::array<tetra, 20>::const_iterator tetra_access::begin() const;
    friend std::array<tetra, 20>::const_iterator tetra_access::end() const;
  };

}
