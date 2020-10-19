#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>
#include <sf/face.h>
#include <sf/field.h>
#include <sf/mat4.h>
#include <sf/shape.h>

namespace sf {

  template <typename T, size_t size>
  class geom {
    static size_t shape_len_from_lod(unsigned);
    static size_t vert_count_from_shape_len(unsigned);
    static size_t shape_count_from_shape_len(unsigned);
    template <typename U, size_t count>
    static std::vector<std::vector<U>> components_from_lod(unsigned);
    static std::vector<shape> shapes_from_lod(unsigned);
    template <typename U> static std::vector<typename std::vector<U>::iterator> iters_from_vec(std::vector<std::vector<U>>&);
    template <typename U> static void counts_from_iters(std::vector<size_t>&, std::vector<typename std::vector<U>::iterator>&, std::vector<std::vector<U>>&);
    std::vector<std::vector<int>> verts;
    std::vector<size_t> vert_counts;
    std::vector<std::vector<T>> data;
    std::vector<size_t> data_counts;
    std::vector<vec3<mpf>> offsets;
    std::vector<shape> shapes;
  public:
    template <typename U> mat4<U> get_transform();
    geom(unsigned);
    const std::vector<std::vector<int>>& get_verts() const;
    const std::vector<size_t>& get_vert_counts() const;
    const std::vector<std::vector<T>>& get_data() const;
    const std::vector<size_t>& get_data_counts() const;
    const std::vector<vec3<mpf>>& get_offsets() const;
    void sample(
      const sf::face::vec_t&,
      std::function<bool(const face::range&)>,
      std::function<void(typename std::vector<T>::iterator&, const face::range&)>
    );
    const unsigned lod;
  };

  template <typename T, size_t size>
  template <typename U>
  inline mat4<U> geom<T, size>::get_transform() {
    return mat4<U>::shear(0, 0, 0, -1, 0, 0) * mat4<U>::shear(.5, 0, 0, 0, 0, 0) * mat4<U>::shear(0, 0, 0, 1, 0, 0);
  }

  template <typename T, size_t size>
  inline size_t geom<T, size>::shape_len_from_lod(unsigned lod) {
    return 1 << (lod + 2);
  }

  template <typename T, size_t size>
  inline size_t geom<T, size>::vert_count_from_shape_len(unsigned len) {
    return 4 * len * (4 * len - 1) * (len + 1);
  }

  template <typename T, size_t size>
  inline size_t geom<T, size>::shape_count_from_shape_len(unsigned len) {
    return len * (2 * len * len - 1);
  }

  template <typename T, size_t size>
  template <typename U, size_t count>
  inline std::vector<std::vector<U>> geom<T, size>::components_from_lod(unsigned lod) {
    auto level_count = field::level_count_from_lod(lod);
    std::vector<std::vector<U>> levels(level_count);
    for (auto& components : levels) {
      auto component_count = count * vert_count_from_shape_len(shape_len_from_lod(lod));
      if (level_count-- > 1) {
        component_count -= count * vert_count_from_shape_len(shape_len_from_lod(lod) / 2);
      }
      components.resize(component_count);
    }
    return levels;
  }

  template <typename T, size_t size>
  inline std::vector<shape> geom<T, size>::shapes_from_lod(unsigned lod) {
    const auto level_count = field::level_count_from_lod(lod);
    const auto shape_len = shape_len_from_lod(lod);
    const auto shape_count = level_count * shape_count_from_shape_len(shape_len + 2) - (level_count - 1) * shape_count_from_shape_len(shape_len / 2 + 2);
    return std::vector<shape>(shape_count);
  }

  template <typename T, size_t size>
  template <typename U>
  inline std::vector<typename std::vector<U>::iterator> geom<T, size>::iters_from_vec(std::vector<std::vector<U>>& vec) {
    std::vector<typename std::vector<U>::iterator> iters(vec.size());
    auto curr_iter = iters.begin();
    for (auto& f : vec) {
      *curr_iter++ = f.begin();
    }
    return iters;
  }

  template <typename T, size_t size>
  template <typename U>
  inline void geom<T, size>::counts_from_iters(std::vector<size_t>& counts, std::vector<typename std::vector<U>::iterator>& iters, std::vector<std::vector<U>>& vec) {
    auto iter = vec.begin();
    auto count_iter = counts.begin();
    for (const auto& curr_iter : iters) {
      *count_iter++ = std::distance((iter++)->begin(), curr_iter);
    }
  }

  template <typename T, size_t size>
  inline geom<T, size>::geom(unsigned lod) :
    lod(lod),
    verts(components_from_lod<int, 3>(lod)),
    vert_counts(verts.size()),
    data(components_from_lod<T, size>(lod)),
    data_counts(data.size()),
    offsets(field::level_count_from_lod(lod)),
    shapes(shapes_from_lod(lod)) {
  }

  template <typename T, size_t size>
  inline const std::vector<std::vector<int>>& geom<T, size>::get_verts() const {
    return verts;
  }

  template <typename T, size_t size>
  inline const std::vector<size_t>& geom<T, size>::get_vert_counts() const {
    return vert_counts;
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
  inline const std::vector<vec3<mpf>>& geom<T, size>::get_offsets() const {
    return offsets;
  }

  template <typename T, size_t size>
  inline void geom<T, size>::sample(
    const face::vec_t& vec,
    std::function<bool(const face::range&)> is_filled,
    std::function<void(typename std::vector<T>::iterator&, const face::range&)> get_data
  ) {
    const auto coords = face::coords_from_vec(vec);
    const auto vert = face::vert_from_vec(coords);
    const auto origin = face::point_from_vert(face::vert_from_vec(vec));
    auto point = face::point_from_vert(vert);
    face::coord_t len = 1;
    for (auto offset = offsets.rbegin(); offset != offsets.rend(); offset++) {
      *offset = origin - (point / len) * len;
      len <<= 1;
    }
    auto vert_iters = iters_from_vec(verts);
    auto data_iters = iters_from_vec(data);
    shape::sample(shapes.begin(), lod, coords, is_filled).map<T>(vert_iters, data_iters, vert, get_data);
    counts_from_iters(vert_counts, vert_iters, verts);
    counts_from_iters(data_counts, data_iters, data);
  }

}
