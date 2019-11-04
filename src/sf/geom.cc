#include <algorithm>
#include <iterator>
#include <cmath>
#include <stdexcept>
#include "geom.h"

const static sf::face::ucoord_t visible_range_len = 2 * sf::face::coord_max;
const static unsigned visible_range_log = std::log2(visible_range_len);

static std::vector<int> verts_from_lod(unsigned lod) {
  const auto len = (1 << (lod + 2)) + 1;
  const auto count = ((1 + (1lu << (lod + 2))) * (3 + (1lu << (lod + 4)) + (1lu << (5 + 2 * lod)))) / 3;
  std::vector<int> verts(3 * count);
  auto curr = verts.begin();
  for (auto i = -len / 2; i <= len / 2; i++) {
    for (auto j = -len / 2; j <= len / 2; j++) {
      for (auto k = -len / 2; k <= len / 2; k++) {
        if (i + j + k >= -len / 2 && i + j + k <= len / 2) {
          *curr++ = i;
          *curr++ = j;
          *curr++ = k;
        }
      }
    }
  }
  return verts;
}

static std::map<std::tuple<int, int, int>, unsigned> map_verts(const std::vector<int>& verts) {
  std::map<std::tuple<int, int, int>, unsigned> verts_map;
  for (auto i = 0u; i < verts.size(); i += 3) {
    verts_map.insert(std::make_pair(std::make_tuple(verts[i + 0], verts[i + 1], verts[i + 2]), i));
  }
  return verts_map;
}

static size_t indices_count_from_lod(unsigned lod) {
  return std::log2(visible_range_len) - lod - 1;
}

static size_t index_count_from_len(sf::face::ucoord_t len) {
  return 4 * len * (4 * len - 1) * (len + 1);
}

static std::vector<std::vector<unsigned>> indices_from_lod(unsigned lod) {
  auto indices_count = indices_count_from_lod(lod);
  std::vector<std::vector<unsigned>> indices(indices_count);
  for (auto& indices : indices) {
    auto index_count = index_count_from_len(1lu << (lod + 2));
    if (indices_count-- > 1) {
      index_count -= index_count_from_len(1lu << (lod + 1));
    }
    indices.resize(index_count);
  }
  return indices;
}

sf::geom::shape::shape() {
}

sf::geom::shape::shape(bool filled) :
  filled(filled) {
}

sf::geom::shape::shape(size_t index) :
  index(index) {
}

void sf::geom::shape::sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t)>) {
  throw std::runtime_error("Attempted to sample base shape object");
}

void sf::geom::shape::map(std::vector<std::vector<unsigned>::iterator>&) const {
  throw std::runtime_error("Attempted to map base shape object");
}

static bool should_split(const sf::face::range_t& range, int lod, int depth) {
  const auto log = visible_range_log - depth;
  const auto len = 1l << log;
  const auto start = sf::face::range_t(visible_range_len / 2) - range;
  const auto end = start - len;
  const auto max = static_cast<sf::face::coord_t>(visible_range_len) >> std::max(depth - lod, 1);
  return len > 1
    && start[0] <= max && end[0] >= -max
    && start[1] <= max && end[1] >= -max
    && start[2] <= max && end[2] >= -max
    && start[3] <= max && end[3] >= -max;
}

static bool is_in_bounds(const sf::face::range_t& range, sf::face::ucoord_t len) {
  return len <= sf::face::coord_max
    && ((range[0] >= 0 && range[0] <= sf::face::coord_max) || (range[0] + len >= 0 && range[0] + len <= sf::face::coord_max))
    && ((range[1] >= 0 && range[1] <= sf::face::coord_max) || (range[1] + len >= 0 && range[1] + len <= sf::face::coord_max))
    && ((range[2] >= 0 && range[2] <= sf::face::coord_max) || (range[2] + len >= 0 && range[2] + len <= sf::face::coord_max))
    && ((range[3] >= 0 && range[3] <= sf::face::coord_max) || (range[3] + len >= 0 && range[3] + len <= sf::face::coord_max));
}

const sf::geom::tet_in* sf::geom::tet_in::placeholder(bool filled) {
  static const tet_in tin_filled(true);
  static const tet_in tin_empty(false);
  if (filled) {
    return &tin_filled;
  }
  return &tin_empty;
}

sf::geom::tet_in::tet_in(bool filled) :
  shape(filled) {
}

sf::geom::tet_in::tet_in(const verts_map_t& verts_map, unsigned lod, const face::range_t& range, unsigned depth) :
  shape(static_cast<size_t>(depth - lod - 2)) {
  auto log = visible_range_log - depth;
  auto len = 1l << log;
  face::range_t r;
  if (should_split(range, lod, depth)) {
    field.resize(5);
    len /= 2;
    log--;
    // Instantiate octahedron.
    r = range + len;
    field[0].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    // Instantiate inward tetrahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    r[2] += len;
    field[1].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[1] += len;
    r[3] += len;
    field[2].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[2] += len;
    r[3] += len;
    field[3].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    r[2] += len;
    r[3] += len;
    field[4].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
  } else {
    r = (range - visible_range_len / 2) / len;
    faces.resize(4);
    // a out
    faces[0] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
    };
    // b out
    faces[1] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 1)),
    };
    // c out
    faces[2] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
    };
    // d out
    faces[3] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
    };
  }
}

void sf::geom::tet_in::sample(const face::range_t& range, face::ucoord_t len, std::function<bool(const face::range_t&, face::coord_t)> is_filled) {
  filled = is_filled(range, len);
  in_bounds = is_in_bounds(range, len);
  if (filled && field.size()) {
    face::range_t r;
    len /= 2;
    // Sample octahedron.
    r = range + len;
    field[0]->sample(r, len, is_filled);
    // Sample inward tetrahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    r[2] += len;
    field[1]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[1] += len;
    r[3] += len;
    field[2]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[2] += len;
    r[3] += len;
    field[3]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    r[2] += len;
    r[3] += len;
    field[4]->sample(r, len, is_filled);
  }
}

void sf::geom::tet_in::map(std::vector<std::vector<unsigned>::iterator>& indices) const {
  if (filled && field.size()) {
    for (const auto& shape : field) {
      shape->map(indices);
    }
    dynamic_cast<oct*>(field[0].get())->map_a(indices, dynamic_cast<tet_in*>(field[4].get()));
    dynamic_cast<oct*>(field[0].get())->map_b(indices, dynamic_cast<tet_in*>(field[3].get()));
    dynamic_cast<oct*>(field[0].get())->map_c(indices, dynamic_cast<tet_in*>(field[2].get()));
    dynamic_cast<oct*>(field[0].get())->map_d(indices, dynamic_cast<tet_in*>(field[1].get()));
  }
}

const sf::geom::tet_out* sf::geom::tet_out::placeholder(bool filled) {
  static const tet_out tout_filled(true);
  static const tet_out tout_empty(false);
  if (filled) {
    return &tout_filled;
  }
  return &tout_empty;
}

sf::geom::tet_out::tet_out(bool filled) :
  shape(filled) {
}

sf::geom::tet_out::tet_out(const verts_map_t& verts_map, unsigned lod, const face::range_t& range, unsigned depth) :
  shape(static_cast<size_t>(depth - lod - 2)) {
  auto log = visible_range_log - depth;
  auto len = 1l << log;
  face::range_t r;
  if (should_split(range, lod, depth)) {
    field.resize(5);
    len /= 2;
    log--;
    // Instantiate octahedron.
    r = range;
    field[0].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    // Instantiate outward tetrahedrons.
    r = range;
    r[0] += len;
    field[1].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    field[2].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[2] += len;
    field[3].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[3] += len;
    field[4].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
  } else {
    r = (range - visible_range_len / 2) / len;
    faces.resize(4);
    // a in
    faces[0] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 0)),
    };
    // b in
    faces[1] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
    };
    // c in
    faces[2] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
    };
    // d in
    faces[3] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
    };
  }
}

void sf::geom::tet_out::sample(const face::range_t& range, face::ucoord_t len, std::function<bool(const face::range_t&, face::coord_t)> is_filled) {
  filled = is_filled(range, len);
  in_bounds = is_in_bounds(range, len);
  if (filled && field.size()) {
    face::range_t r;
    len /= 2;
    // Sample octahedron.
    r = range;
    field[0]->sample(r, len, is_filled);
    // Sample outward tetrahedrons.
    r = range;
    r[0] += len;
    field[1]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    field[2]->sample(r, len, is_filled);
    r = range;
    r[2] += len;
    field[3]->sample(r, len, is_filled);
    r = range;
    r[3] += len;
    field[4]->sample(r, len, is_filled);
  }
}

void sf::geom::tet_out::map(std::vector<std::vector<unsigned>::iterator>& indices) const {
  if (filled && field.size()) {
    for (const auto& shape : field) {
      shape->map(indices);
    }
    dynamic_cast<oct*>(field[0].get())->map_a(indices, dynamic_cast<tet_out*>(field[1].get()));
    dynamic_cast<oct*>(field[0].get())->map_b(indices, dynamic_cast<tet_out*>(field[2].get()));
    dynamic_cast<oct*>(field[0].get())->map_c(indices, dynamic_cast<tet_out*>(field[3].get()));
    dynamic_cast<oct*>(field[0].get())->map_d(indices, dynamic_cast<tet_out*>(field[4].get()));
  }
}

const sf::geom::oct* sf::geom::oct::placeholder(bool filled) {
  static const oct oct_filled(true);
  static const oct oct_empty(false);
  if (filled) {
    return &oct_filled;
  }
  return &oct_empty;
}

sf::geom::oct::oct(bool filled) :
  shape(filled) {
}

sf::geom::oct::oct(const verts_map_t& verts_map, unsigned lod, const face::range_t& range, unsigned depth) :
  shape(static_cast<size_t>(depth - lod - 2)) {
  auto log = visible_range_log - depth;
  auto len = 1l << log;
  face::range_t r;
  if (should_split(range, lod, depth)) {
    field.resize(14);
    len /= 2;
    log--;
    // Instantiate octahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    field[0].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[2] += len;
    field[1].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[3] += len;
    field[2].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    r[2] += len;
    field[3].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    r[3] += len;
    field[4].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    r = range;
    r[2] += len;
    r[3] += len;
    field[5].reset(new sf::geom::oct(verts_map, lod, r, depth + 1));
    // Instantiate inward tetrahedrons.
    r = range;
    r[0] += len;
    field[6].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    field[7].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[2] += len;
    field[8].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    r = range;
    r[3] += len;
    field[9].reset(new sf::geom::tet_in(verts_map, lod, r, depth + 1));
    // Instantiate outward tetrahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    r[2] += len;
    field[10].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[1] += len;
    r[3] += len;
    field[11].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[0] += len;
    r[2] += len;
    r[3] += len;
    field[12].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
    r = range;
    r[1] += len;
    r[2] += len;
    r[3] += len;
    field[13].reset(new sf::geom::tet_out(verts_map, lod, r, depth + 1));
  } else {
    r = (range - visible_range_len / 2) / len;
    faces.resize(8);
    // a in
    faces[0] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
    };
    // a out
    faces[1] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
    };
    // b in
    faces[2] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
    };
    // b out
    faces[3] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
    };
    // c in
    faces[4] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
    };
    // c out
    faces[5] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
    };
    // d in
    faces[6] = {
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 1, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 1)),
    };
    // d out
    faces[7] = {
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 0, r[2] + 1)),
      verts_map.at(std::make_tuple(r[0] + 1, r[1] + 0, r[2] + 0)),
      verts_map.at(std::make_tuple(r[0] + 0, r[1] + 1, r[2] + 0)),
    };
  }
}

void sf::geom::oct::sample(const face::range_t& range, face::ucoord_t len, std::function<bool(const face::range_t&, face::coord_t)> is_filled) {
  filled = is_filled(range, len);
  in_bounds = is_in_bounds(range, len);
  if (filled && field.size()) {
    face::range_t r;
    len /= 2;
    // Sample octahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    field[0]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[2] += len;
    field[1]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[3] += len;
    field[2]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    r[2] += len;
    field[3]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    r[3] += len;
    field[4]->sample(r, len, is_filled);
    r = range;
    r[2] += len;
    r[3] += len;
    field[5]->sample(r, len, is_filled);
    // Sample inward tetrahedrons.
    r = range;
    r[0] += len;
    field[6]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    field[7]->sample(r, len, is_filled);
    r = range;
    r[2] += len;
    field[8]->sample(r, len, is_filled);
    r = range;
    r[3] += len;
    field[9]->sample(r, len, is_filled);
    // Sample outward tetrahedrons.
    r = range;
    r[0] += len;
    r[1] += len;
    r[2] += len;
    field[10]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[1] += len;
    r[3] += len;
    field[11]->sample(r, len, is_filled);
    r = range;
    r[0] += len;
    r[2] += len;
    r[3] += len;
    field[12]->sample(r, len, is_filled);
    r = range;
    r[1] += len;
    r[2] += len;
    r[3] += len;
    field[13]->sample(r, len, is_filled);
  }
}

void sf::geom::oct::map_a(std::vector<std::vector<unsigned>::iterator>& indices, const tet_in* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_in*, 3> tin;
    const tet_out* tout;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[3].get());
        o[1] = dynamic_cast<oct*>(field[4].get());
        o[2] = dynamic_cast<oct*>(field[5].get());
        tout = dynamic_cast<tet_out*>(field[13].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tout = tet_out::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tin[0] = dynamic_cast<tet_in*>(tet->field[1].get());
        tin[1] = dynamic_cast<tet_in*>(tet->field[2].get());
        tin[2] = dynamic_cast<tet_in*>(tet->field[3].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tin.begin(), tin.end(), tet_in::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_a(indices, tin[0]);
      o[1]->map_a(indices, tin[1]);
      o[2]->map_a(indices, tin[2]);
      o[3]->map_a(indices, tout);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[0].begin(), faces[0].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[0].begin(), tet->faces[0].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_a(std::vector<std::vector<unsigned>::iterator>& indices, const tet_out* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_out*, 3> tout;
    const tet_in* tin;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[0].get());
        o[1] = dynamic_cast<oct*>(field[1].get());
        o[2] = dynamic_cast<oct*>(field[2].get());
        tin = dynamic_cast<tet_in*>(field[7].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tin = tet_in::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tout[0] = dynamic_cast<tet_out*>(tet->field[2].get());
        tout[1] = dynamic_cast<tet_out*>(tet->field[3].get());
        tout[2] = dynamic_cast<tet_out*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tout.begin(), tout.end(), tet_out::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_a(indices, tout[0]);
      o[1]->map_a(indices, tout[1]);
      o[2]->map_a(indices, tout[2]);
      o[3]->map_a(indices, tin);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[1].begin(), faces[1].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[0].begin(), tet->faces[0].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_b(std::vector<std::vector<unsigned>::iterator>& indices, const tet_in* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_in*, 3> tin;
    const tet_out* tout;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[1].get());
        o[1] = dynamic_cast<oct*>(field[2].get());
        o[2] = dynamic_cast<oct*>(field[5].get());
        tout = dynamic_cast<tet_out*>(field[12].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tout = tet_out::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tin[0] = dynamic_cast<tet_in*>(tet->field[1].get());
        tin[1] = dynamic_cast<tet_in*>(tet->field[2].get());
        tin[2] = dynamic_cast<tet_in*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tin.begin(), tin.end(), tet_in::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_b(indices, tin[0]);
      o[1]->map_b(indices, tin[1]);
      o[2]->map_b(indices, tin[2]);
      o[3]->map_b(indices, tout);
    } else if ((filled && in_bounds && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[2].begin(), faces[2].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[1].begin(), tet->faces[1].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_b(std::vector<std::vector<unsigned>::iterator>& indices, const tet_out* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_out*, 3> tout;
    const tet_in* tin;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[0].get());
        o[1] = dynamic_cast<oct*>(field[3].get());
        o[2] = dynamic_cast<oct*>(field[4].get());
        tin = dynamic_cast<tet_in*>(field[7].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tin = tet_in::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tout[0] = dynamic_cast<tet_out*>(tet->field[1].get());
        tout[1] = dynamic_cast<tet_out*>(tet->field[3].get());
        tout[2] = dynamic_cast<tet_out*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tout.begin(), tout.end(), tet_out::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_b(indices, tout[0]);
      o[1]->map_b(indices, tout[1]);
      o[2]->map_b(indices, tout[2]);
      o[3]->map_b(indices, tin);
    } else if ((filled && in_bounds && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[3].begin(), faces[3].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[1].begin(), tet->faces[1].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_c(std::vector<std::vector<unsigned>::iterator>& indices, const tet_in* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_in*, 3> tin;
    const tet_out* tout;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[0].get());
        o[1] = dynamic_cast<oct*>(field[2].get());
        o[2] = dynamic_cast<oct*>(field[4].get());
        tout = dynamic_cast<tet_out*>(field[11].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tout = tet_out::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tin[0] = dynamic_cast<tet_in*>(tet->field[1].get());
        tin[1] = dynamic_cast<tet_in*>(tet->field[3].get());
        tin[2] = dynamic_cast<tet_in*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tin.begin(), tin.end(), tet_in::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_c(indices, tin[0]);
      o[1]->map_c(indices, tin[1]);
      o[2]->map_c(indices, tin[2]);
      o[3]->map_c(indices, tout);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[4].begin(), faces[4].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[2].begin(), tet->faces[2].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_c(std::vector<std::vector<unsigned>::iterator>& indices, const tet_out* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_out*, 3> tout;
    const tet_in* tin;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[1].get());
        o[1] = dynamic_cast<oct*>(field[3].get());
        o[2] = dynamic_cast<oct*>(field[5].get());
        tin = dynamic_cast<tet_in*>(field[8].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tin = tet_in::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tout[0] = dynamic_cast<tet_out*>(tet->field[1].get());
        tout[1] = dynamic_cast<tet_out*>(tet->field[2].get());
        tout[2] = dynamic_cast<tet_out*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tout.begin(), tout.end(), tet_out::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_c(indices, tout[0]);
      o[1]->map_c(indices, tout[1]);
      o[2]->map_c(indices, tout[2]);
      o[3]->map_c(indices, tin);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[5].begin(), faces[5].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[2].begin(), tet->faces[2].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_d(std::vector<std::vector<unsigned>::iterator>& indices, const tet_in* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_in*, 3> tin;
    const tet_out* tout;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[0].get());
        o[1] = dynamic_cast<oct*>(field[1].get());
        o[2] = dynamic_cast<oct*>(field[3].get());
        tout = dynamic_cast<tet_out*>(field[10].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tout = tet_out::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tin[0] = dynamic_cast<tet_in*>(tet->field[1].get());
        tin[1] = dynamic_cast<tet_in*>(tet->field[3].get());
        tin[2] = dynamic_cast<tet_in*>(tet->field[4].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tin.begin(), tin.end(), tet_in::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_d(indices, tin[0]);
      o[1]->map_d(indices, tin[1]);
      o[2]->map_d(indices, tin[2]);
      o[3]->map_d(indices, tout);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[6].begin(), faces[6].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[3].begin(), tet->faces[3].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map_d(std::vector<std::vector<unsigned>::iterator>& indices, const tet_out* tet) const {
  if (filled || tet->filled) {
    std::array<const oct*, 3> o;
    std::array<const tet_out*, 3> tout;
    const tet_in* tin;
    if (field.size() || tet->field.size()) {
      if (filled && field.size()) {
        o[0] = dynamic_cast<oct*>(field[2].get());
        o[1] = dynamic_cast<oct*>(field[4].get());
        o[2] = dynamic_cast<oct*>(field[5].get());
        tin = dynamic_cast<tet_in*>(field[9].get());
      } else {
        std::fill(o.begin(), o.end(), oct::placeholder(filled));
        tin = tet_in::placeholder(filled);
      }
      if (tet->filled && tet->field.size()) {
        tout[0] = dynamic_cast<tet_out*>(tet->field[1].get());
        tout[1] = dynamic_cast<tet_out*>(tet->field[2].get());
        tout[2] = dynamic_cast<tet_out*>(tet->field[3].get());
        o[3] = dynamic_cast<oct*>(tet->field[0].get());
      } else {
        std::fill(tout.begin(), tout.end(), tet_out::placeholder(tet->filled));
        o[3] = oct::placeholder(tet->filled);
      }
      o[0]->map_d(indices, tout[0]);
      o[1]->map_d(indices, tout[1]);
      o[2]->map_d(indices, tout[2]);
      o[3]->map_d(indices, tin);
    } else if ((in_bounds && filled && !tet->filled) || (!filled && tet->in_bounds && tet->filled)) {
      if (faces.size()) {
        std::copy(faces[7].begin(), faces[7].end(), indices[index]);
        indices[index] += 3;
      } else if (tet->faces.size()) {
        std::copy(tet->faces[3].begin(), tet->faces[3].end(), indices[tet->index]);
        indices[tet->index] += 3;
      } else {
        throw std::runtime_error("Attempted to map shapes without face data");
      }
    }
  }
}

void sf::geom::oct::map(std::vector<std::vector<unsigned>::iterator>& indices) const {
  if (filled && field.size()) {
    for (const auto& shape : field) {
      shape->map(indices);
    }
    dynamic_cast<oct*>(field[0].get())->map_a(indices, dynamic_cast<tet_in*>(field[7].get()));
    dynamic_cast<oct*>(field[0].get())->map_b(indices, dynamic_cast<tet_in*>(field[6].get()));
    dynamic_cast<oct*>(field[0].get())->map_c(indices, dynamic_cast<tet_out*>(field[10].get()));
    dynamic_cast<oct*>(field[0].get())->map_d(indices, dynamic_cast<tet_out*>(field[11].get()));
    dynamic_cast<oct*>(field[1].get())->map_a(indices, dynamic_cast<tet_in*>(field[8].get()));
    dynamic_cast<oct*>(field[1].get())->map_b(indices, dynamic_cast<tet_out*>(field[10].get()));
    dynamic_cast<oct*>(field[1].get())->map_c(indices, dynamic_cast<tet_in*>(field[6].get()));
    dynamic_cast<oct*>(field[1].get())->map_d(indices, dynamic_cast<tet_out*>(field[12].get()));
    dynamic_cast<oct*>(field[2].get())->map_a(indices, dynamic_cast<tet_in*>(field[9].get()));
    dynamic_cast<oct*>(field[2].get())->map_b(indices, dynamic_cast<tet_out*>(field[11].get()));
    dynamic_cast<oct*>(field[2].get())->map_c(indices, dynamic_cast<tet_out*>(field[12].get()));
    dynamic_cast<oct*>(field[2].get())->map_d(indices, dynamic_cast<tet_in*>(field[6].get()));
    dynamic_cast<oct*>(field[3].get())->map_a(indices, dynamic_cast<tet_out*>(field[10].get()));
    dynamic_cast<oct*>(field[3].get())->map_b(indices, dynamic_cast<tet_in*>(field[8].get()));
    dynamic_cast<oct*>(field[3].get())->map_c(indices, dynamic_cast<tet_in*>(field[7].get()));
    dynamic_cast<oct*>(field[3].get())->map_d(indices, dynamic_cast<tet_out*>(field[13].get()));
    dynamic_cast<oct*>(field[4].get())->map_a(indices, dynamic_cast<tet_out*>(field[11].get()));
    dynamic_cast<oct*>(field[4].get())->map_b(indices, dynamic_cast<tet_in*>(field[9].get()));
    dynamic_cast<oct*>(field[4].get())->map_c(indices, dynamic_cast<tet_out*>(field[13].get()));
    dynamic_cast<oct*>(field[4].get())->map_d(indices, dynamic_cast<tet_in*>(field[7].get()));
    dynamic_cast<oct*>(field[5].get())->map_a(indices, dynamic_cast<tet_out*>(field[12].get()));
    dynamic_cast<oct*>(field[5].get())->map_b(indices, dynamic_cast<tet_out*>(field[13].get()));
    dynamic_cast<oct*>(field[5].get())->map_c(indices, dynamic_cast<tet_in*>(field[9].get()));
    dynamic_cast<oct*>(field[5].get())->map_d(indices, dynamic_cast<tet_in*>(field[8].get()));
  }
}

sf::geom::geom(unsigned lod) :
  lod(lod),
  verts(verts_from_lod(lod)),
  indices(indices_from_lod(lod)),
  index_counts(indices.size()),
  field(map_verts(verts), lod) {
}

const std::vector<int>& sf::geom::get_verts() const {
  return verts;
}

const std::vector<std::vector<unsigned>>& sf::geom::get_indices() const {
  return indices;
}

const std::vector<size_t>& sf::geom::get_index_counts() const {
  return index_counts;
}

void sf::geom::sample(const face::vec_t& v, std::function<bool(const face::range_t&, face::coord_t)> is_filled) {
  const auto range = sf::face::range_t(
    sf::mpf::round(v[0]),
    sf::mpf::round(v[1]),
    sf::mpf::round(v[2]),
    sf::mpf::round(v[3])
  ) - visible_range_len / 2;
  field.sample(range, visible_range_len, is_filled);
  std::vector<std::vector<unsigned>::iterator> iters(indices.size());
  auto curr_iter = iters.begin();
  for (auto& index : indices) {
    *curr_iter++ = index.begin();
  }
  field.map(iters);
  auto curr_index = indices.begin();
  auto curr_count = index_counts.begin();
  for (const auto& iter : iters) {
    printf("%lu\n", std::distance(curr_index->begin(), iter));
    *curr_count++ = std::distance((curr_index++)->begin(), iter);
  }
}
