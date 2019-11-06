#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <iterator>
#include <vector>
#include <stdexcept>
#include <sf/face.h>
#include <sf/shape.h>

namespace sf {

  template <typename T, size_t size>
  class geom {
    static size_t indices_count_from_lod(unsigned);
    static std::vector<std::vector<unsigned>> indices_from_lod(unsigned);
    static std::vector<std::vector<T>> data_from_lod(unsigned);
    static std::vector<std::vector<std::vector<bool>>> filled_faces_from_lod(unsigned);
    const std::vector<int> verts;
    std::vector<std::vector<unsigned>> indices;
    std::vector<size_t> index_counts;
    std::vector<std::vector<T>> data;
    std::vector<size_t> data_counts;
    std::vector<std::vector<std::vector<bool>>> filled_faces;
    shape<T, size> field;
  public:
    typedef enum {oct, tet_in, tet_out} shape_t;
    geom(unsigned);
    const std::vector<int>& get_verts() const;
    const std::vector<std::vector<unsigned>>& get_indices() const;
    const std::vector<size_t>& get_index_counts() const;
    const std::vector<std::vector<T>>& get_data() const;
    const std::vector<size_t>& get_data_counts() const;
    void sample(
      const face::vec_t&,
      std::function<bool(const face::range_t&, face::coord_t len)>,
      std::function<std::array<T, size>(const face::range_t&, face::coord_t len, shape_t)>
    );
    const unsigned lod;
  };

  size_t vert_count_from_lod(unsigned lod) {
    return ((1 + (1lu << (lod + 2))) * (3 + (1lu << (lod + 4)) + (1lu << (5 + 2 * lod)))) / 3;
  }

  inline std::vector<int> verts_from_lod(unsigned lod) {
    const auto len = (1 << (lod + 2)) + 1;
    const auto count = 3 * vert_count_from_lod(lod);
    std::vector<int> verts(count);
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

  inline std::map<std::tuple<int, int, int>, unsigned> map_verts(const std::vector<int>& verts) {
    std::map<std::tuple<int, int, int>, unsigned> verts_map;
    for (auto i = 0u; i < verts.size(); i += 3) {
      verts_map.insert(std::make_pair(std::make_tuple(verts[i + 0], verts[i + 1], verts[i + 2]), i));
    }
    return verts_map;
  }

  template <typename T, size_t size>
  inline size_t geom<T, size>::indices_count_from_lod(unsigned lod) {
    return std::log2(shape<T, size>::visible_range_len) - lod - 1;
  }

  inline size_t index_count_from_len(face::ucoord_t len) {
    return (4 * len * (4 * len - 1) * (len + 1)) / 3;
  }

  template <typename T, size_t size>
  inline std::vector<std::vector<unsigned>> geom<T, size>::indices_from_lod(unsigned lod) {
    auto indices_count = indices_count_from_lod(lod);
    std::vector<std::vector<unsigned>> indices(indices_count);
    for (auto& idx : indices) {
      auto count = 2 * 3 * index_count_from_len(1lu << (lod + 2));
      if (count-- > 1) {
        count -= 2 * 3 * index_count_from_len(1lu << (lod + 1));
      }
      idx.resize(count);
    }
    return indices;
  }

  inline size_t shape_count_from_lod(unsigned lod) {
    return (1 << (2 + lod)) * ((1 << (5 + 2 * lod)) - 1);
  }

  template <typename T, size_t size>
  inline std::vector<std::vector<T>> geom<T, size>::data_from_lod(unsigned lod) {
    auto data_count = indices_count_from_lod(lod);
    std::vector<std::vector<T>> data(data_count);
    for (auto& d : data) {
      auto count = size * shape_count_from_lod(lod);
      if (data_count-- > 1) {
        count -= size * shape_count_from_lod(lod - 1);
      }
      d.resize(count);
    }
    return data;
  }

  template <typename T, size_t size>
  inline std::vector<std::vector<std::vector<bool>>> geom<T, size>::filled_faces_from_lod(unsigned lod) {
    auto filled_faces_count = indices_count_from_lod(lod);
    std::vector<std::vector<std::vector<bool>>> filled_faces(filled_faces_count);
    for (auto& f : filled_faces) {
      auto count = shape_count_from_lod(lod);
      if (filled_faces_count-- > 1) {
        count -= shape_count_from_lod(lod - 1);
      }
      f.resize(count);
    }
    return filled_faces;
  }

  template <typename T>
  inline std::vector<typename std::vector<T>::iterator> iters_from_vec(std::vector<std::vector<T>>& vec) {
    std::vector<typename std::vector<T>::iterator> iters(vec.size());
    auto curr_iter = iters.begin();
    for (auto& f : vec) {
      *curr_iter++ = f.begin();
    }
    return iters;
  }

  template <typename T>
  inline void counts_from_iters(std::vector<size_t>& counts, std::vector<typename std::vector<T>::iterator>& iters, std::vector<std::vector<T>>& vec) {
    counts.resize(iters.size());
    auto iter = vec.begin();
    auto count_iter = counts.begin();
    for (const auto& curr_iter : iters) {
      *count_iter++ = std::distance((iter++)->begin(), curr_iter);
    }
  }

  template <typename T, size_t size>
  inline geom<T, size>::geom(unsigned lod) :
    lod(lod),
    verts(verts_from_lod(lod)),
    data(data_from_lod(lod)),
    indices(indices_from_lod(lod)),
    filled_faces(filled_faces_from_lod(lod)),
    field(shape<T, size>::oct_from_lod(lod, iters_from_vec(filled_faces), map_verts(verts))) {
  }

  template <typename T, size_t size>
  inline const std::vector<int>& geom<T, size>::get_verts() const {
    return verts;
  }

  template <typename T, size_t size>
  inline const std::vector<std::vector<unsigned>>& geom<T, size>::get_indices() const {
    return indices;
  }

  template <typename T, size_t size>
  inline const std::vector<size_t>& geom<T, size>::get_index_counts() const {
    return index_counts;
  }

  template <typename T, size_t size>
  inline const std::vector<std::vector<T>>& geom<T, size>::get_data() const {
    return data;
  }

  template <typename T, size_t size>
  inline const std::vector<size_t>& geom<T, size>::get_data_counts() const {
    return data_counts;
  }

  template <typename T, size_t size>
  inline void geom<T, size>::sample(
    const face::vec_t& v,
    std::function<bool(const face::range_t&, face::coord_t)> is_filled,
    std::function<std::array<T, size>(const face::range_t&, face::coord_t, shape_t)> fill_data
  ) {
    const auto range = face::range_t(
      mpf::round(v[0]),
      mpf::round(v[1]),
      mpf::round(v[2]),
      mpf::round(v[3])
    ) - shape<T, size>::visible_range_len / 2;
    std::vector<typename std::vector<T>::iterator> data_begin(iters_from_vec(data));
    std::vector<typename std::vector<T>::iterator> data_iters(iters_from_vec(data));
    field.sample(
      data_begin,
      data_iters,
      filled_faces,
      range,
      shape<T, size>::visible_range_len,
      is_filled,
      [&](const face::range_t& range, face::coord_t len, typename shape<T, size>::type_t shape) {
        return fill_data(range, len, static_cast<shape_t>(shape));
      }
    );
    counts_from_iters(data_counts, data_iters, data);
    std::vector<std::vector<unsigned>::iterator> index_iters(iters_from_vec(indices));
    field.map(index_iters, filled_faces);
    counts_from_iters(index_counts, index_iters, indices);
  }

}
