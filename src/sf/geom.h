#pragma once

#include <array>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include <vector>
#include "face.h"
#include "vec3.h"

namespace sf {

  class geom {
    typedef std::map<std::tuple<int, int, int>, unsigned> verts_map_t;
    class shape {
    public:
      shape();
      shape(bool);
      shape(size_t);
      virtual void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      virtual void map(std::vector<std::vector<unsigned>::iterator>&) const;
      std::vector<std::unique_ptr<shape>> field;
      size_t index;
      std::vector<std::array<unsigned, 3>> faces;
      bool filled;
      bool in_bounds;
    };
    class tet_in : public shape {
    public:
      static const tet_in* placeholder(bool);
      tet_in(bool);
      tet_in(const verts_map_t&, unsigned, const face::range_t&, unsigned);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
    };
    class tet_out : public shape {
    public:
      static const tet_out* placeholder(bool);
      tet_out(bool);
      tet_out(const verts_map_t&, unsigned, const face::range_t&, unsigned);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
    };
    class oct : public shape {
    public:
      static const oct* placeholder(bool);
      oct(bool);
      oct(const verts_map_t&, unsigned, const face::range_t& = face::range_t(), unsigned = 0);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
      void map_a(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_a(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_b(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_b(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_c(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_c(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_d(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_d(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
    };
    const std::vector<int> verts;
    std::vector<std::vector<unsigned>> indices;
    std::vector<size_t> index_counts;
    oct field;
  public:
    geom(unsigned);
    const std::vector<int>& get_verts() const;
    const std::vector<std::vector<unsigned>>& get_indices() const;
    const std::vector<size_t>& get_index_counts() const;
    void sample(const face::vec_t&, std::function<bool(const face::range_t&, face::coord_t len)>);
    const unsigned lod;
  };

}
