#include "vec3.h"

std::array<sf::mpf, 3>::iterator sf::vec3::begin() {
  return xyz.begin();
}

std::array<sf::mpf, 3>::const_iterator sf::vec3::begin() const {
  return xyz.begin();
}

std::array<sf::mpf, 3>::iterator sf::vec3::end() {
  return xyz.end();
}

std::array<sf::mpf, 3>::const_iterator sf::vec3::end() const {
  return xyz.end();
}

size_t sf::vec3::size() const {
  return 3;
}

sf::mpf sf::vec3::length() const {
  return mpf::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
}

sf::vec3 sf::vec3::unit() const {
  return *this / length();
}

void sf::vec3::unitize() {
  *this /= length();
}

sf::vec3 sf::vec3::operator-() const {
  return vec3(-xyz[0], -xyz[1], -xyz[2]);
}

sf::vec3 sf::vec3::operator+(const vec3& v) const {
  return vec3(xyz[0] + v[0], xyz[1] + v[1], xyz[2] + v[2]);
}

sf::vec3 sf::vec3::operator-(const vec3& v) const {
  return vec3(xyz[0] - v[0], xyz[1] - v[1], xyz[2] - v[2]);
}

sf::vec3 sf::vec3::operator*(const vec3& v) const {
  return vec3(
    xyz[1] * v[2] - xyz[2] * v[1],
    xyz[2] * v[0] - xyz[0] * v[2],
    xyz[0] * v[1] - xyz[1] * v[0]
  );
}

sf::mpf sf::vec3::operator^(const vec3& v) const {
  return xyz[0] * v[0] + xyz[1] * v[1] + xyz[2] * v[2];
}

sf::mpf& sf::vec3::operator[](size_t n) {
  return xyz[n];
}

const sf::mpf& sf::vec3::operator[](size_t n) const {
  return xyz[n];
}
