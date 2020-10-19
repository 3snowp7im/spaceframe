#pragma once

#include <array>
#include <functional>
#include <memory>
#include <vector>
#include <sf/face.h>

namespace sf {

  class shape {
    typedef enum {oct, tet_in, tet_out} type_t;
    typedef enum {in, out} dir_t;
    typedef enum {a, b, c, d} axis_t;
    struct srange {
      face::coords_t start;
      face::coords_t len;
    };
    static bool should_split(const face::range&, const srange&);
    void sample(
      std::vector<shape>::iterator&,
      unsigned,
      unsigned,
      type_t,
      size_t,
      const face::range&,
      std::vector<srange>::const_iterator,
      std::function<bool(const face::range&)>
    );
    std::array<shape*, 4> shapes_from_axis(axis_t, dir_t) const;
    std::array<face::coords_t, 3> face_coords_from_range(axis_t, dir_t) const;
    template <typename T>
    void map(
      std::vector<std::vector<int>::iterator>&,
      std::vector<typename std::vector<T>::iterator>&,
      const vec3<face::coord_t>&,
      std::function<void(typename std::vector<T>::iterator&, const face::range&)>,
      axis_t,
      shape*
    );
  public:
    static shape& sample(
      std::vector<shape>::iterator,
      unsigned,
      const face::coords_t&,
      std::function<bool(const face::range&)>
    );
    template <typename T>
    void map(
      std::vector<std::vector<int>::iterator>&,
      std::vector<typename std::vector<T>::iterator>&,
      const vec3<face::coord_t>&,
      std::function<void(typename std::vector<T>::iterator&, const face::range&)>
    );
    type_t type;
    size_t index;
    face::range range;
    bool filled;
    bool split;
    std::array<shape*, 14> field;
    std::array<std::array<bool, 2>, 4> filled_faces;
  };

  inline shape& shape::sample(
    std::vector<shape>::iterator shape,
    unsigned lod,
    const face::coords_t& origin,
    std::function<bool(const face::range&)> is_filled
  ) {
    auto& root = *shape++;
    std::vector<srange> visible_ranges(face::coord_max_log2 - lod);
    face::coords_t curr_start = origin;
    face::coords_t curr_end = face::coords_t(face::coord_max) - origin;
    face::coord_t len = 1 << lod;
    for (auto visible_range = visible_ranges.rbegin(); visible_range != visible_ranges.rend(); visible_range++) {
      curr_start = ((((curr_start / len) - 1) * len) / 2) * 2;
      curr_end = ((((curr_end / len) - 1) * len) / 2) * 2;
      visible_range->start = curr_start;
      visible_range->len = face::coords_t(face::coord_max) - curr_end - curr_start;
      len <<= 1;
    }
    const face::range shape_range = {vec4<face::ucoord_t>(0), static_cast<face::ucoord_t>(face::coord_max)};
    root.sample(shape, 0, lod, oct, face::coord_max_log2 - lod - 1, shape_range, visible_ranges.begin(), is_filled);
    return root;
  }

  inline bool shape::should_split(const face::range& a, const srange& b) {
    face::coords_t as(a.start);
    return ((as[0] >= b.start[0] && as[0] < b.start[0] + b.len[0]) || (as[0] + a.len >= b.start[0] && as[0] + a.len < b.start[0] + b.len[0]))
        && ((as[1] >= b.start[1] && as[1] < b.start[1] + b.len[1]) || (as[1] + a.len >= b.start[1] && as[1] + a.len < b.start[1] + b.len[1]))
        && ((as[2] >= b.start[2] && as[2] < b.start[2] + b.len[2]) || (as[2] + a.len >= b.start[2] && as[2] + a.len < b.start[2] + b.len[2]))
        && ((as[3] >= b.start[3] && as[3] < b.start[3] + b.len[3]) || (as[3] + a.len >= b.start[3] && as[3] + a.len < b.start[3] + b.len[3]));
  }

  inline void shape::sample(
    std::vector<shape>::iterator& shape,
    unsigned lod,
    unsigned lod_max,
    type_t type,
    size_t index,
    const face::range& range,
    std::vector<srange>::const_iterator visible_range,
    std::function<bool(const face::range&)> is_filled
  ) {
    this->type = type;
    this->index = index;
    this->range = range;
    this->filled = is_filled(range);
    for (auto& axis : this->filled_faces) {
      std::fill(axis.begin(), axis.end(), false);
    }
    if (!this->filled || index == 0) {
      return;
    }
    bool lod_split = lod < lod_max;
    bool range_split = should_split(range, *visible_range);
    if (!lod_split && !range_split) {
      this->split = false;
      return;
    }
    this->split = true;
    if (range_split) {
      lod = 0;
    } else {
      lod++;
    }
    face::range r = range;
    r.len /= 2;
    index--;
    visible_range++;
    switch (type) {
    case tet_in:
      // Sample octahedron.
      r.start = range.start + r.len;
      field[0] = &*shape++;
      field[0]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      // Sample inward tetrahedrons.
      r.start = range.start;
      r.start[0] += r.len;
      r.start[1] += r.len;
      r.start[2] += r.len;
      field[1] = &*shape++;
      field[1]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[1] += r.len;
      r.start[3] += r.len;
      field[2] = &*shape++;
      field[2]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[2] += r.len;
      r.start[3] += r.len;
      field[3] = &*shape++;
      field[3]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      r.start[2] += r.len;
      r.start[3] += r.len;
      field[4] = &*shape++;
      field[4]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      break;
    case tet_out:
      // Sample octahedron.
      r.start = range.start;
      field[0] = &*shape++;
      field[0]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      // Sample outward tetrahedrons.
      r.start = range.start;
      r.start[0] += r.len;
      field[1] = &*shape++;
      field[1]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      field[2] = &*shape++;
      field[2]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[2] += r.len;
      field[3] = &*shape++;
      field[3]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[3] += r.len;
      field[4] = &*shape++;
      field[4]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      break;
    case oct:
      // Sample octahedrons.
      r.start = range.start;
      r.start[0] += r.len;
      r.start[1] += r.len;
      field[0] = &*shape++;
      field[0]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[2] += r.len;
      field[1] = &*shape++;
      field[1]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[3] += r.len;
      field[2] = &*shape++;
      field[2]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      r.start[2] += r.len;
      field[3] = &*shape++;
      field[3]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      r.start[3] += r.len;
      field[4] = &*shape++;
      field[4]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[2] += r.len;
      r.start[3] += r.len;
      field[5] = &*shape++;
      field[5]->sample(shape, lod, lod_max, oct, index, r, visible_range, is_filled);
      // Sample inward tetrahedrons.
      r.start = range.start;
      r.start[0] += r.len;
      field[6] = &*shape++;
      field[6]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      field[7] = &*shape++;
      field[7]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[2] += r.len;
      field[8] = &*shape++;
      field[8]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[3] += r.len;
      field[9] = &*shape++;
      field[9]->sample(shape, lod, lod_max, tet_in, index, r, visible_range, is_filled);
      // Sample outward tetrahedrons.
      r.start = range.start;
      r.start[0] += r.len;
      r.start[1] += r.len;
      r.start[2] += r.len;
      field[10] = &*shape++;
      field[10]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[1] += r.len;
      r.start[3] += r.len;
      field[11] = &*shape++;
      field[11]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[0] += r.len;
      r.start[2] += r.len;
      r.start[3] += r.len;
      field[12] = &*shape++;
      field[12]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      r.start = range.start;
      r.start[1] += r.len;
      r.start[2] += r.len;
      r.start[3] += r.len;
      field[13] = &*shape++;
      field[13]->sample(shape, lod, lod_max, tet_out, index, r, visible_range, is_filled);
      break;
    }
  }

  template <typename T>
  inline void shape::map(
    std::vector<std::vector<int>::iterator>& verts,
    std::vector<typename std::vector<T>::iterator>& data,
    const vec3<face::coord_t>& origin,
    std::function<void(typename std::vector<T>::iterator&, const face::range&)> get_data
  ) {
    if (filled && split) {
      size_t shape_count;
      switch (type) {
      case tet_in:
        shape_count = 5;
        field[1]->map<T>(verts, data, origin, get_data, d, field[0]);
        field[2]->map<T>(verts, data, origin, get_data, c, field[0]);
        field[3]->map<T>(verts, data, origin, get_data, b, field[0]);
        field[4]->map<T>(verts, data, origin, get_data, a, field[0]);
        break;
      case tet_out:
        shape_count = 5;
        field[0]->map<T>(verts, data, origin, get_data, a, field[1]);
        field[0]->map<T>(verts, data, origin, get_data, b, field[2]);
        field[0]->map<T>(verts, data, origin, get_data, c, field[3]);
        field[0]->map<T>(verts, data, origin, get_data, d, field[4]);
        break;
      case oct:
        shape_count = 14;
        field[0]->map<T>(verts, data, origin, get_data, c, field[10]);
        field[0]->map<T>(verts, data, origin, get_data, d, field[11]);
        field[1]->map<T>(verts, data, origin, get_data, b, field[10]);
        field[1]->map<T>(verts, data, origin, get_data, d, field[12]);
        field[2]->map<T>(verts, data, origin, get_data, b, field[11]);
        field[2]->map<T>(verts, data, origin, get_data, c, field[12]);
        field[3]->map<T>(verts, data, origin, get_data, a, field[10]);
        field[3]->map<T>(verts, data, origin, get_data, d, field[13]);
        field[4]->map<T>(verts, data, origin, get_data, a, field[11]);
        field[4]->map<T>(verts, data, origin, get_data, c, field[13]);
        field[5]->map<T>(verts, data, origin, get_data, a, field[12]);
        field[5]->map<T>(verts, data, origin, get_data, b, field[13]);
        field[6]->map<T>(verts, data, origin, get_data, b, field[0]);
        field[6]->map<T>(verts, data, origin, get_data, c, field[1]);
        field[6]->map<T>(verts, data, origin, get_data, d, field[2]);
        field[7]->map<T>(verts, data, origin, get_data, a, field[0]);
        field[7]->map<T>(verts, data, origin, get_data, c, field[3]);
        field[7]->map<T>(verts, data, origin, get_data, d, field[4]);
        field[8]->map<T>(verts, data, origin, get_data, a, field[1]);
        field[8]->map<T>(verts, data, origin, get_data, b, field[3]);
        field[8]->map<T>(verts, data, origin, get_data, d, field[5]);
        field[9]->map<T>(verts, data, origin, get_data, a, field[2]);
        field[9]->map<T>(verts, data, origin, get_data, b, field[4]);
        field[9]->map<T>(verts, data, origin, get_data, c, field[5]);
        break;
      }
      for (int i = 0; i < shape_count; i++) {
        field[i]->map<T>(verts, data, origin, get_data);
      }
    }
  }

  inline std::array<shape*, 4> shape::shapes_from_axis(axis_t axis, dir_t dir) const {
    switch (type) {
    case tet_in:
      switch (dir) {
      case out:
        switch (axis) {
        case a:
          return std::array<shape*, 4>({field[1], field[2], field[3], field[0]});
        case b:
          return std::array<shape*, 4>({field[1], field[2], field[4], field[0]});
        case c:
          return std::array<shape*, 4>({field[1], field[3], field[4], field[0]});
        case d:
          return std::array<shape*, 4>({field[2], field[3], field[4], field[0]});
        }
      }
      break;
    case tet_out:
      switch (dir) {
      case in:
        switch (axis) {
        case a:
          return std::array<shape*, 4>({field[2], field[3], field[4], field[0]});
        case b:
          return std::array<shape*, 4>({field[1], field[3], field[4], field[0]});
        case c:
          return std::array<shape*, 4>({field[1], field[2], field[4], field[0]});
        case d:
          return std::array<shape*, 4>({field[1], field[2], field[3], field[0]});
        }
      }
      break;
    case oct:
      switch (dir) {
      case in:
        switch (axis) {
        case a:
          return std::array<shape*, 4>({field[3], field[4], field[5], field[13]});
        case b:
          return std::array<shape*, 4>({field[1], field[2], field[5], field[12]});
        case c:
          return std::array<shape*, 4>({field[0], field[2], field[4], field[11]});
        case d:
          return std::array<shape*, 4>({field[0], field[1], field[3], field[10]});
        }
        break;
      case out:
        switch (axis) {
        case a:
          return std::array<shape*, 4>({field[0], field[1], field[2], field[6]});
        case b:
          return std::array<shape*, 4>({field[0], field[3], field[4], field[7]});
        case c:
          return std::array<shape*, 4>({field[1], field[3], field[5], field[8]});
        case d:
          return std::array<shape*, 4>({field[2], field[4], field[5], field[9]});
        }
        break;
      }
      break;
    }
    throw std::runtime_error("shape::shapes_from_axis: invalid shape for axis direction");
  }

  inline std::array<face::coords_t, 3> shape::face_coords_from_range(axis_t axis, dir_t dir) const {
    face::coords_t r(range.start[0], range.start[1], range.start[2], range.start[3]);
    face::coord_t len = range.len;
    switch (type) {
    case tet_in:
      switch (dir) {
      case out:
        switch (axis) {
        case a:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1], r[2] + len, r[3] + len
          }, {
            r[0] + len, r[1] + len, r[2] + len, r[3]
          }, {
            r[0] + len, r[1] + len, r[2], r[3] + len
          }}});
        case b:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1] + len, r[2] + len, r[3] + len
          }, {
            r[0] + len, r[1] + len, r[2], r[3] + len
          }, {
            r[0] + len, r[1] + len, r[2] + len, r[3]
          }}});
        case c:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2] + len, r[3]
          }, {
            r[0] + len, r[1], r[2] + len, r[3] + len
          }, {
            r[0], r[1] + len, r[2] + len, r[3] + len
          }}});
        case d:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2], r[3] + len
          }, {
            r[0], r[1] + len, r[2] + len, r[3] + len
          }, {
            r[0] + len, r[1], r[2] + len, r[3] + len
          }}});
        }
        break;
      }
      break;
    case tet_out:
      switch (dir) {
      case in:
        switch (axis) {
        case a:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1] + len, r[2], r[3]
          }, {
            r[0], r[1], r[2] + len, r[3]
          }, {
            r[0], r[1], r[2], r[3] + len
          }}});
        case b:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1], r[2], r[3]
          }, {
            r[0], r[1], r[2], r[3] + len
          }, {
            r[0], r[1], r[2] + len, r[3]
          }}});
        case c:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2], r[3] + len
          }, {
            r[0] + len, r[1], r[2], r[3]
          }, {
            r[0], r[1] + len, r[2], r[3]
          }}});
        case d:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2] + len, r[3]
          }, {
            r[0], r[1] + len, r[2], r[3]
          }, {
            r[0] + len, r[1], r[2], r[3]
          }}});
        }
        break;
      }
      break;
    case oct:
      switch (dir) {
      case in:
        switch (axis) {
        case a:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2] + len, r[3] + len
          }, {
            r[0], r[1] + len, r[2], r[3] + len
          }, {
            r[0], r[1] + len, r[2] + len, r[3]
          }}});
        case b:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2] + len, r[3] + len
          }, {
            r[0] + len, r[1], r[2] + len, r[3]
          }, {
            r[0] + len, r[1], r[2], r[3] + len
          }}});
        case c:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2], r[3]
          }, {
            r[0], r[1] + len, r[2], r[3] + len
          }, {
            r[0] + len, r[1], r[2], r[3] + len
          }}});
        case d:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2], r[3]
          }, {
            r[0] + len, r[1], r[2] + len, r[3]
          }, {
            r[0], r[1] + len, r[2] + len, r[3]
          }}});
        }
        break;
      case out:
        switch (axis) {
        case a:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2], r[3]
          }, {
            r[0] + len, r[1], r[2], r[3] + len
          }, {
            r[0] + len, r[1], r[2] + len, r[3]
          }}});
        case b:
          return std::array<face::coords_t, 3>({{{
            r[0] + len, r[1] + len, r[2], r[3]
          }, {
            r[0], r[1] + len, r[2] + len, r[3]
          }, {
            r[0], r[1] + len, r[2], r[3] + len
          }}});
        case c:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2] + len, r[3] + len
          }, {
            r[0], r[1] + len, r[2] + len, r[3]
          }, {
            r[0] + len, r[1], r[2] + len, r[3]
          }}});
        case d:
          return std::array<face::coords_t, 3>({{{
            r[0], r[1], r[2] + len, r[3] + len
          }, {
            r[0] + len, r[1], r[2], r[3] + len
          }, {
            r[0], r[1] + len, r[2], r[3] + len
          }}});
        }
      }
      break;
    }
    throw std::runtime_error("shape::face_coords_from_range: invalid shape for axis direction");
  }

  template <typename T>
  inline void shape::map(
    std::vector<std::vector<int>::iterator>& verts,
    std::vector<typename std::vector<T>::iterator>& data,
    const vec3<face::coord_t>& origin,
    std::function<void(typename std::vector<T>::iterator&, const face::range&)> get_data,
    axis_t axis,
    shape* out
  ) {
    shape* in = this;
    if (in->filled || out->filled) {
      if ((in->filled && in->split) || (out->filled && out->split)) {
        std::array<shape*, 4> in_shapes;
        std::array<shape*, 4> out_shapes;
        if (in->filled && in->split) {
          in_shapes = in->shapes_from_axis(axis, dir_t::out);
        } else {
          std::fill(in_shapes.begin(), in_shapes.end(), in);
        }
        if (out->filled && out->split) {
          out_shapes = out->shapes_from_axis(axis, dir_t::in);
        } else {
          std::fill(out_shapes.begin(), out_shapes.end(), out);
        }
        for (int i = 0; i < 4; i++) {
          in_shapes[i]->map<T>(verts, data, origin, get_data, axis, out_shapes[i]);
        }
      } else if ((in->filled && !out->filled) || (!in->filled && out->filled)) {
        std::array<face::coords_t, 3> face_coords;
        face::ucoord_t len;
        bool filled = false;
        if (in->filled && !in->filled_faces[static_cast<size_t>(axis)][static_cast<size_t>(dir_t::out)]) {
          in->filled_faces[static_cast<size_t>(axis)][static_cast<size_t>(dir_t::out)] = true;
          face_coords = in->face_coords_from_range(axis, dir_t::out);
          len = in->range.len;
        } else if (out->filled && !out->filled_faces[static_cast<size_t>(axis)][static_cast<size_t>(dir_t::in)]) {
          out->filled_faces[static_cast<size_t>(axis)][static_cast<size_t>(dir_t::in)] = true;
          face_coords = out->face_coords_from_range(axis, dir_t::in);
          len = out->range.len;
        } else {
          filled = true;
        }
        if (!filled) {
          for (auto& coords : face_coords) {
            auto vert = face::vert_from_vec(coords) / len - origin / len;
            std::copy(vert.begin(), vert.end(), verts[index]);
            verts[index] += 3;
          }
          for (int i = 0; i < 3; i++) {
            face::range r = {face_coords[i], range.len};
            get_data(data[index], r);
          }
        }
      }
    }
  }

}
