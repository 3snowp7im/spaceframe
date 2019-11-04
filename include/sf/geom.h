#pragma once

#include <array>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include <vector>
#include <sf/face.h>
#include <sf/sf.h>

namespace sf {

  class geom {
    typedef std::map<std::tuple<int, int, int>, unsigned> verts_map_t;
    class shape {
    public:
      shape();
      shape(bool, bool);
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
      static const tet_in* placeholder(bool, bool);
      tet_in(bool, bool);
      tet_in(const verts_map_t&, unsigned, const face::range_t&, unsigned);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
    };
    class tet_out : public shape {
    public:
      static const tet_out* placeholder(bool, bool);
      tet_out(bool, bool);
      tet_out(const verts_map_t&, unsigned, const face::range_t&, unsigned);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
    };
    class oct : public shape {
    public:
      static const oct* placeholder(bool, bool);
      oct(bool, bool);
      oct(const verts_map_t&, unsigned, const face::range_t& = face::range_t(), unsigned = 0);
      void sample(const face::range_t&, face::ucoord_t, std::function<bool(const face::range_t&, face::coord_t len)>);
      template <typename M, typename T, typename U, size_t a, size_t b, size_t c, size_t d, size_t e, size_t f, size_t g, size_t x>
      void map(std::vector<std::vector<unsigned>::iterator>&, const T*) const;
      void map_a(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_a(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_b(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_b(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_c(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_c(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map_d(std::vector<std::vector<unsigned>::iterator>&, const tet_in*) const;
      void map_d(std::vector<std::vector<unsigned>::iterator>&, const tet_out*) const;
      void map(std::vector<std::vector<unsigned>::iterator>&) const;
    };
    struct mapper_a {
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_in* t) {
        o->map_a(indices, t);
      }
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_out* t) {
        o->map_a(indices, t);
      }
    };
    struct mapper_b {
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_in* t) {
        o->map_b(indices, t);
      }
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_out* t) {
        o->map_b(indices, t);
      }
    };
    struct mapper_c {
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_in* t) {
        o->map_c(indices, t);
      }
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_out* t) {
        o->map_c(indices, t);
      }
    };
    struct mapper_d {
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_in* t) {
        o->map_d(indices, t);
      }
      static inline void map(std::vector<std::vector<unsigned>::iterator>& indices, const oct* o, const tet_out* t) {
        o->map_d(indices, t);
      }
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
