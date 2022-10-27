#ifndef TYPES_HH
#define TYPES_HH

#include <array>
#include <algorithm>

namespace Types {

  using data_t = double;
  using point_4d_t = std::array<data_t, 4>; // (t, x, y, z)
  using point_3d_t = std::array<data_t, 3>; // (x, y, z)
  using field_t = std::array<data_t, 3>; // (Ex, Ey, Ez)
  using vector_t = std::array<data_t, 3>; // any three-dimensional vector

  template <typename T, std::size_t n>
  void add(const std::array<T, n>& arg1, const std::array<T, n>& arg2, std::array<T, n>& res) {
    std::transform(arg1.cbegin(), arg1.cend(), arg2.cbegin(), res.begin(), std::plus<T>{});
  }

  template <typename T, std::size_t n>
  void mul(const std::array<T, n>& arg1, data_t arg2, std::array<T, n>& res) {
    std::transform(arg1.cbegin(), arg1.cend(), res.begin(), [&](const T cur){return arg2 * cur;});
  }

  template <typename T, std::size_t n>
  std::array<T, n> add(const std::array<T, n>& arg1, const std::array<T, n>& arg2) {
    std::array<T, n> retval;
    add(arg1, arg2, retval);
    return retval;
  }

  // Argh. Can't simply overload operator*, because ADL won't find it in this namespace 
  // (since only aliases of std types are involved, only the std namespace is searched)
  template <typename T, std::size_t n>
  std::array<T, n> mul(const std::array<T, n>& arg1, data_t arg2) {
    std::array<T, n> retval;
    mul(arg1, arg2, retval);
    return retval;
  }

  template <typename T, std::size_t n>
  std::string to_string(const std::array<T, n>& arg1) {
    std::string retval;
    for(T cur: arg1) {
      retval += std::to_string(cur) + " ";
    }
    return retval;
  }
}

#endif
