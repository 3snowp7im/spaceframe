#pragma once

#include <array>
#include <sf/face.h>
#include <sf/mpf.h>
#include <sf/sf.h>
#include <sf/vec3.h>

namespace sf {

  class spheroid {
    static void init();
    static std::array<face, 20> face_array;
    class face_access {
    public:
      const face& operator[](size_t) const;
      std::array<face, 20>::const_iterator begin() const;
      std::array<face, 20>::const_iterator end() const;
    };
  public:
    spheroid() = delete;
    static sf::vec3<sf::mpf> face_pos_from_point(const vec3<mpf>&);
    constexpr static face_access faces = face_access();
    friend void sf::init();
    friend const face& face_access::operator[](size_t i) const;
    friend std::array<face, 20>::const_iterator face_access::begin() const;
    friend std::array<face, 20>::const_iterator face_access::end() const;
  };

}
