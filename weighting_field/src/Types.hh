#ifndef TYPES_HH
#define TYPES_HH

#include <array>

namespace Types {

  using data_t = double;
  using point_t = std::array<data_t, 4>; // (t, x, y, z)
  using field_t = std::array<data_t, 3>; // (Ex, Ey, Ez)
  
}

#endif
