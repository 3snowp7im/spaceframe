#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include <vector>
#include <sf/face.h>

namespace sf {

  template <typename T, size_t size>
  class geom;

  template <typename T, size_t size>
  class shape {
    typedef enum {oct, tet_in, tet_out} type_t;
    typedef enum {a, b, c, d} axis_t;
    typedef enum {in, out} dir_t;
    typedef std::map<std::tuple<int, int, int>, unsigned> verts_map_t;
    static shape<T, size> oct_from_lod(int, std::vector<std::vector<std::vector<bool>>::iterator>, const verts_map_t&);
    static std::vector<std::unique_ptr<shape<T, size>>> field_from_range(
      const std::vector<std::vector<std::vector<bool>>::iterator>&,
      std::vector<std::vector<std::vector<bool>>::iterator>&,
      type_t,
      const verts_map_t&,
      int,
      const face::range_t&,
      int
    );
    static std::vector<std::array<unsigned, 3>> faces_from_type(type_t, const verts_map_t&, const face::range_t&, int);
    static size_t filled_faces_index_from_iters(const std::vector<std::vector<bool>>::iterator&, std::vector<std::vector<bool>>::iterator&, type_t);
    static bool should_split(const face::range_t&, int, int);
    shape();
    shape(
      const std::vector<std::vector<std::vector<bool>>::iterator>&,
      std::vector<std::vector<std::vector<bool>>::iterator>&,
      type_t,
      const verts_map_t&,
      int,
      const face::range_t&,
      int
    );
    std::array<const shape*, 4> shapes_from_axis(axis_t, dir_t) const;
    void sample(
      const std::vector<typename std::vector<T>::iterator>&,
      std::vector<typename std::vector<T>::iterator>&,
      std::vector<std::vector<std::vector<bool>>>&,
      const face::range_t&,
      face::ucoord_t,
      std::function<bool(const face::range_t&, face::coord_t)>,
      std::function<std::array<T, size>(const face::range_t&, face::coord_t, type_t)>
    );
    void map(std::vector<std::vector<unsigned>::iterator>&, std::vector<std::vector<std::vector<bool>>>&) const;
    void map(std::vector<std::vector<unsigned>::iterator>&, std::vector<std::vector<std::vector<bool>>>&, axis_t, const shape<T, size>*) const;
    std::vector<std::unique_ptr<shape<T, size>>> field;
    type_t type;
    ssize_t index;
    ssize_t data_index;
    ssize_t faces_index;
    std::vector<std::array<unsigned, 3>> faces;
    bool filled;
    bool in_bounds;
    constexpr static unsigned visible_range_log = std::log2(face::coord_max) + 1;
  public:
    constexpr static face::ucoord_t visible_range_len = 2 * face::coord_max;
    friend class geom<T, size>;
  };

  template <typename T, size_t size>
  inline shape<T, size>::shape() {
  }

  template <typename T, size_t size>
  inline bool shape<T, size>::should_split(const face::range_t& range, int lod, int depth) {
    const auto log = visible_range_log - depth;
    const auto len = 1l << log;
    const auto start = face::range_t(visible_range_len / 2) - range;
    const auto end = start - len;
    const auto max = static_cast<face::coord_t>(visible_range_len) >> std::max(depth - lod, 1);
    return len > 1
      && start[0] <= max && end[0] >= -max
      && start[1] <= max && end[1] >= -max
      && start[2] <= max && end[2] >= -max
      && start[3] <= max && end[3] >= -max;
  }

  inline bool is_in_bounds(const face::range_t& range, face::ucoord_t len) {
    return ((range[0] >= 0 && range[0] <= face::coord_max) || (range[0] + len >= 0 && range[0] + len <= face::coord_max) || (range[0] <= 0 && range[0] + len >= face::coord_max))
      && ((range[1] >= 0 && range[1] <= face::coord_max) || (range[1] + len >= 0 && range[1] + len <= face::coord_max) || (range[1] <= 0 && range[1] + len >= face::coord_max))
      && ((range[2] >= 0 && range[2] <= face::coord_max) || (range[2] + len >= 0 && range[2] + len <= face::coord_max) || (range[2] <= 0 && range[2] + len >= face::coord_max))
      && ((range[3] >= 0 && range[3] <= face::coord_max) || (range[3] + len >= 0 && range[3] + len <= face::coord_max) || (range[3] <= 0 && range[3] + len >= face::coord_max));
  }

  template <typename T, size_t size>
  inline std::vector<std::unique_ptr<shape<T, size>>> shape<T, size>::field_from_range(
    const std::vector<std::vector<std::vector<bool>>::iterator>& filled_faces_begin,
    std::vector<std::vector<std::vector<bool>>::iterator>& filled_faces_iter,
    type_t type,
    const verts_map_t& verts_map,
    int lod,
    const face::range_t& range,
    int depth
  ) {
    auto log = shape<T, size>::visible_range_log - depth;
    auto len = 1l << log;
    std::vector<std::unique_ptr<shape<T, size>>> field;
    if (should_split(range, lod, depth)) {
      face::range_t r;
      len /= 2;
      log--;
      switch (type) {
      case type_t::tet_in:
        field.resize(5);
        // Instantiate octahedron.
        r = range + len;
        field[0].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        // Instantiate inward tetrahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        r[2] += len;
        field[1].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[1] += len;
        r[3] += len;
        field[2].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[2] += len;
        r[3] += len;
        field[3].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        r[2] += len;
        r[3] += len;
        field[4].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        break;
      case type_t::tet_out:
        field.resize(5);
        // Instantiate octahedron.
        r = range;
        field[0].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        // Instantiate outward tetrahedrons.
        r = range;
        r[0] += len;
        field[1].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        field[2].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[2] += len;
        field[3].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[3] += len;
        field[4].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        break;
      case type_t::oct:
        field.resize(14);
        // Instantiate octahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        field[0].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[2] += len;
        field[1].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[3] += len;
        field[2].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        r[2] += len;
        field[3].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        r[3] += len;
        field[4].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        r = range;
        r[2] += len;
        r[3] += len;
        field[5].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::oct, verts_map, lod, r, depth + 1));
        // Instantiate inward tetrahedrons.
        r = range;
        r[0] += len;
        field[6].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        field[7].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[2] += len;
        field[8].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        r = range;
        r[3] += len;
        field[9].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_in, verts_map, lod, r, depth + 1));
        // Instantiate outward tetrahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        r[2] += len;
        field[10].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[1] += len;
        r[3] += len;
        field[11].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[0] += len;
        r[2] += len;
        r[3] += len;
        field[12].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        r = range;
        r[1] += len;
        r[2] += len;
        r[3] += len;
        field[13].reset(new shape<T, size>(filled_faces_begin, filled_faces_iter, type_t::tet_out, verts_map, lod, r, depth + 1));
        break;
      }
    }
    return field;
  }

  template <typename T, size_t size>
  inline std::vector<std::array<unsigned, 3>> shape<T, size>::faces_from_type(
    type_t type,
    const verts_map_t& verts_map,
    const face::range_t& range,
    int depth
  ) {
    auto log = visible_range_log - depth;
    auto len = 1l << log;
    std::vector<std::array<unsigned, 3>> faces;
    face::range_t r = (range - visible_range_len / 2) / len;
    switch (type) {
    case type_t::tet_in:
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
      break;
    case tet_out:
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
      break;
    case oct:
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
      break;
    }
    return faces;
  }

  template <typename T, size_t size>
  inline size_t shape<T, size>::filled_faces_index_from_iters(
    const std::vector<std::vector<bool>>::iterator& begin,
    std::vector<std::vector<bool>>::iterator& iter,
    type_t type
  ) {
    auto filled_faces_index = std::distance(begin, iter);
    switch (type) {
    case type_t::tet_in:
    case type_t::tet_out:
      (iter++)->resize(4);
      break;
    case type_t::oct:
      (iter++)->resize(8);
      break;
    }
    return filled_faces_index;
  }

  template <typename T, size_t size>
  inline shape<T, size> shape<T, size>::oct_from_lod(
    int lod,
    std::vector<std::vector<std::vector<bool>>::iterator> filled_faces_iters,
    const verts_map_t& verts_map
  ) {
    const std::vector<std::vector<std::vector<bool>>::iterator> begin(filled_faces_iters);
    return shape<T, size>(begin, filled_faces_iters, type_t::oct, verts_map, lod, face::range_t(), 0);
  }

  template <typename T, size_t size>
  inline shape<T, size>::shape(
    const std::vector<std::vector<std::vector<bool>>::iterator>& filled_faces_begin,
    std::vector<std::vector<std::vector<bool>>::iterator>& filled_faces_iter,
    type_t type,
    const verts_map_t& verts_map,
    int lod,
    const face::range_t& range,
    int depth
  ) :
    type(type),
    index(depth - lod - 2),
    field(field_from_range(filled_faces_begin, filled_faces_iter, type, verts_map, lod, range, depth)),
    faces(field.size() ? std::vector<std::array<unsigned, 3>>() : faces_from_type(type, verts_map, range, depth)),
    faces_index(field.size() ? -1 : filled_faces_index_from_iters(filled_faces_begin[index], filled_faces_iter[index], type)) {
  }

  template <typename T, size_t size>
  inline void shape<T, size>::sample(
    const std::vector<typename std::vector<T>::iterator>& data_begin,
    std::vector<typename std::vector<T>::iterator>& data_iter,
    std::vector<std::vector<std::vector<bool>>>& filled_faces,
    const face::range_t& range,
    face::ucoord_t len,
    std::function<bool(const face::range_t&, face::coord_t)> is_filled,
    std::function<std::array<T, size>(const face::range_t&, face::coord_t, type_t)> fill_data
  ) {
    filled = is_filled(range, len);
    in_bounds = is_in_bounds(range, len);
    if (filled && field.size()) {
      face::range_t r;
      len /= 2;
      switch (type) {
      case tet_in:
        // Sample octahedron.
        r = range + len;
        field[0]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        // Sample inward tetrahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        r[2] += len;
        field[1]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[1] += len;
        r[3] += len;
        field[2]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[2] += len;
        r[3] += len;
        field[3]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        r[2] += len;
        r[3] += len;
        field[4]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        break;
      case tet_out:
        // Sample octahedron.
        r = range;
        field[0]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        // Sample outward tetrahedrons.
        r = range;
        r[0] += len;
        field[1]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        field[2]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[2] += len;
        field[3]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[3] += len;
        field[4]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        break;
      case oct:
        // Sample octahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        field[0]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[2] += len;
        field[1]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[3] += len;
        field[2]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        r[2] += len;
        field[3]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        r[3] += len;
        field[4]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[2] += len;
        r[3] += len;
        field[5]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        // Sample inward tetrahedrons.
        r = range;
        r[0] += len;
        field[6]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        field[7]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[2] += len;
        field[8]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[3] += len;
        field[9]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        // Sample outward tetrahedrons.
        r = range;
        r[0] += len;
        r[1] += len;
        r[2] += len;
        field[10]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[1] += len;
        r[3] += len;
        field[11]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[0] += len;
        r[2] += len;
        r[3] += len;
        field[12]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        r = range;
        r[1] += len;
        r[2] += len;
        r[3] += len;
        field[13]->sample(data_begin, data_iter, filled_faces, r, len, is_filled, fill_data);
        break;
      }
    } else if (!field.size()) {
      const auto data = fill_data(range, len, type);
      std::copy(data.begin(), data.end(), data_iter[index]);
      data_index = std::distance(data_begin[index], data_iter[index]);
      data_iter[index] += size;
      std::fill(filled_faces[index][faces_index].begin(), filled_faces[index][faces_index].end(), false);
    }
  }

  template <typename T, size_t size>
  inline void shape<T, size>::map(std::vector<std::vector<unsigned>::iterator>& indices, std::vector<std::vector<std::vector<bool>>>& filled_faces) const {
    if (filled && field.size()) {
      for (const auto& shape : field) {
        shape->map(indices, filled_faces);
      }
      switch (type) {
      case tet_in:
        field[1]->map(indices, filled_faces, axis_t::d, field[0].get());
        field[2]->map(indices, filled_faces, axis_t::c, field[0].get());
        field[3]->map(indices, filled_faces, axis_t::b, field[0].get());
        field[4]->map(indices, filled_faces, axis_t::a, field[0].get());
        break;
      case tet_out:
        field[0]->map(indices, filled_faces, axis_t::a, field[1].get());
        field[0]->map(indices, filled_faces, axis_t::b, field[2].get());
        field[0]->map(indices, filled_faces, axis_t::c, field[3].get());
        field[0]->map(indices, filled_faces, axis_t::d, field[4].get());
        break;
      case oct:
        field[0]->map(indices, filled_faces, axis_t::c, field[10].get());
        field[0]->map(indices, filled_faces, axis_t::d, field[11].get());
        field[1]->map(indices, filled_faces, axis_t::b, field[10].get());
        field[1]->map(indices, filled_faces, axis_t::d, field[12].get());
        field[2]->map(indices, filled_faces, axis_t::b, field[11].get());
        field[2]->map(indices, filled_faces, axis_t::c, field[12].get());
        field[3]->map(indices, filled_faces, axis_t::a, field[10].get());
        field[3]->map(indices, filled_faces, axis_t::d, field[13].get());
        field[4]->map(indices, filled_faces, axis_t::a, field[11].get());
        field[4]->map(indices, filled_faces, axis_t::c, field[13].get());
        field[5]->map(indices, filled_faces, axis_t::a, field[12].get());
        field[5]->map(indices, filled_faces, axis_t::b, field[13].get());
        field[6]->map(indices, filled_faces, axis_t::b, field[0].get());
        field[6]->map(indices, filled_faces, axis_t::c, field[1].get());
        field[6]->map(indices, filled_faces, axis_t::d, field[2].get());
        field[7]->map(indices, filled_faces, axis_t::a, field[0].get());
        field[7]->map(indices, filled_faces, axis_t::c, field[3].get());
        field[7]->map(indices, filled_faces, axis_t::d, field[4].get());
        field[8]->map(indices, filled_faces, axis_t::a, field[1].get());
        field[8]->map(indices, filled_faces, axis_t::b, field[3].get());
        field[8]->map(indices, filled_faces, axis_t::d, field[5].get());
        field[9]->map(indices, filled_faces, axis_t::a, field[2].get());
        field[9]->map(indices, filled_faces, axis_t::b, field[4].get());
        field[9]->map(indices, filled_faces, axis_t::c, field[5].get());
        break;
      }
    }
  }

  template <typename T, size_t size>
  inline std::array<const shape<T, size>*, 4> shape<T, size>::shapes_from_axis(axis_t axis, dir_t dir) const {
    switch (type) {
    case type_t::tet_in:
      switch (axis) {
      case axis_t::a:
        switch (dir) {
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[2].get(), field[3].get(), field[0].get()});
        }
        break;
      case axis_t::b:
        switch (dir) {
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[2].get(), field[4].get(), field[0].get()});
        }
        break;
      case axis_t::c:
        switch (dir) {
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[3].get(), field[4].get(), field[0].get()});
        }
        break;
      case axis_t::d:
        switch (dir) {
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[2].get(), field[3].get(), field[4].get(), field[0].get()});
        }
        break;
      }
      break;
    case type_t::tet_out:
      switch (axis) {
      case axis_t::a:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[2].get(), field[3].get(), field[4].get(), field[0].get()});
        }
        break;
      case axis_t::b:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[3].get(), field[4].get(), field[0].get()});
        }
        break;
      case axis_t::c:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[2].get(), field[4].get(), field[0].get()});
        }
        break;
      case axis_t::d:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[2].get(), field[3].get(), field[0].get()});
        }
        break;
      }
      break;
    case type_t::oct:
      switch (axis) {
      case axis_t::a:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[3].get(), field[4].get(), field[5].get(), field[13].get()});
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[0].get(), field[1].get(), field[2].get(), field[6].get()});
        }
        break;
      case axis_t::b:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[2].get(), field[5].get(), field[12].get()});
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[0].get(), field[3].get(), field[4].get(), field[7].get()});
        }
        break;
      case axis_t::c:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[0].get(), field[2].get(), field[4].get(), field[11].get()});
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[1].get(), field[3].get(), field[5].get(), field[8].get()});
        }
        break;
      case axis_t::d:
        switch (dir) {
        case dir_t::in:
          return std::array<const shape<T, size>*, 4>({field[0].get(), field[1].get(), field[3].get(), field[10].get()});
        case dir_t::out:
          return std::array<const shape<T, size>*, 4>({field[2].get(), field[4].get(), field[5].get(), field[9].get()});
        }
        break;
      }
      break;
    }
    throw std::runtime_error("Invalid shape for axis direction");
  }

  template <typename T, size_t size>
  inline void shape<T, size>::map(
    std::vector<std::vector<unsigned>::iterator>& indices,
    std::vector<std::vector<std::vector<bool>>>& filled_faces,
    axis_t axis,
    const shape<T, size>* out
  ) const {
    const shape<T, size>* in = this;
    if (in->filled || out->filled) {
      if ((in->filled && in->field.size()) || (out->filled && out->field.size())) {
        std::array<const shape*, 4> in_shapes;
        std::array<const shape*, 4> out_shapes;
        if (in->filled && in->field.size()) {
          in_shapes = in->shapes_from_axis(axis, dir_t::out);
        } else {
          std::fill(in_shapes.begin(), in_shapes.end(), in);
        }
        if (out->filled && out->field.size()) {
          out_shapes = out->shapes_from_axis(axis, dir_t::in);
        } else {
          std::fill(out_shapes.begin(), out_shapes.end(), out);
        }
        for (int i = 0; i < 4; i++) {
          in_shapes[i]->map(indices, filled_faces, axis, out_shapes[i]);
        }
      } else if (in->in_bounds && in->filled && !out->filled) {
        size_t face_index;
        switch (in->type) {
        case type_t::tet_in:
          switch (axis) {
          case axis_t::a:
            face_index = 0;
            break;
          case axis_t::b:
            face_index = 1;
            break;
          case axis_t::c:
            face_index = 2;
            break;
          case axis_t::d:
            face_index = 3;
            break;
          }
          break;
        case type_t::oct:
          switch (axis) {
          case axis_t::a:
            face_index = 1;
            break;
          case axis_t::b:
            face_index = 3;
            break;
          case axis_t::c:
            face_index = 5;
            break;
          case axis_t::d:
            face_index = 7;
            break;
          }
          break;
        default:
          throw std::runtime_error("Invalid shape for axis direction");
        }
        if (!filled_faces[in->index][in->faces_index][face_index]) {
          filled_faces[in->index][in->faces_index][face_index] = true;
          for (int i = 0; i < 3; i++) {
            *indices[in->index]++ = in->faces[face_index][i];
            *indices[in->index]++ = in->data_index;
          }
        }
      } else if (!in->filled && out->in_bounds && out->filled) {
        size_t face_index;
        switch (in->type) {
        case type_t::tet_out:
          switch (axis) {
          case axis_t::a:
            face_index = 0;
            break;
          case axis_t::b:
            face_index = 1;
            break;
          case axis_t::c:
            face_index = 2;
            break;
          case axis_t::d:
            face_index = 3;
            break;
          }
          break;
        case type_t::oct:
          switch (axis) {
          case axis_t::a:
            face_index = 0;
            break;
          case axis_t::b:
            face_index = 2;
            break;
          case axis_t::c:
            face_index = 4;
            break;
          case axis_t::d:
            face_index = 6;
            break;
          }
          break;
        default:
          throw std::runtime_error("Invalid shape for axis direction");
        }
        if (!filled_faces[out->index][out->faces_index][face_index]) {
          filled_faces[out->index][out->faces_index][face_index] = true;
          for (int i = 0; i < 3; i++) {
            *indices[out->index]++ = out->faces[face_index][i];
            *indices[out->index]++ = out->data_index;
          }
        }
      }
    }
  }

}
