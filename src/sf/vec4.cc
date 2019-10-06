#include "vec4.h"

std::array<sf::mpf, 4>::iterator sf::vec4::begin() {
  return xyzw.begin();
}

std::array<sf::mpf, 4>::const_iterator sf::vec4::begin() const {
  return xyzw.begin();
}

std::array<sf::mpf, 4>::iterator sf::vec4::end() {
  return xyzw.end();
}

std::array<sf::mpf, 4>::const_iterator sf::vec4::end() const {
  return xyzw.end();
}

size_t sf::vec4::size() const {
  return 4;
}

sf::mpf sf::vec4::length() const {
  return mpf::sqrt(xyzw[0] * xyzw[0] + xyzw[1] * xyzw[1] + xyzw[2] * xyzw[2] + xyzw[3] * xyzw[3]);
}

sf::vec4 sf::vec4::unit() const {
  return *this / length();
}

void sf::vec4::unitize() {
  *this /= length();
}

sf::vec4::operator vec3() const {
  return vec3(xyzw[0], xyzw[1], xyzw[2]);
}

sf::mpf& sf::vec4::operator[](size_t n) {
  return xyzw[n];
}

const sf::mpf& sf::vec4::operator[](size_t n) const {
  return xyzw[n];
}
