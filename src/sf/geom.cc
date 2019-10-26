#include <cmath>
#include <stdexcept>
#include "geom.h"

size_t sf::geom::range_count_from_lod(size_t lod) {
  auto max_lod = std::log2(tetra::coord_max) - 1;
  if (lod > max_lod) {
    throw std::runtime_error("Max lod is " + std::to_string(max_lod) + " but " + std::to_string(lod) + " given");
  }
  return max_lod - lod;
}

std::vector<int> sf::geom::vertices_from_lod(size_t lod) {
  auto len = 1 + (4 << lod);
  auto count = -(len * (1 + len) * (1 + 2 * len - 3 * (len + 1))) / 6;
  std::vector<int> vertices(3 * count);
  auto curr = vertices.begin();
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      for (int k = 0; k < len && i + j + k < len; k++) {
        *curr++ = i;
        *curr++ = j;
        *curr++ = k;
      }
    }
  }
  return vertices;
}

sf::tetra::range_t sf::geom::viewable_range_from_vec(const sf::tetra::vec_t& v) {
  return sf::tetra::range_t(mpf::round(v[0]), mpf::round(v[1]), mpf::round(v[2]), mpf::round(v[3])) - 2 * tetra::coord_max;
}
