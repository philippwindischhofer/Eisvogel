#ifndef WEIGHTING_FIELD_PROVIDER_HH
#define WEIGHTING_FIELD_PROVIDER_HH

#include <array>

namespace WeightingFieldProvider {

  using data_t = double;
  using point_t = std::array<data_t, 4>; // (t, x, y, z)
  using field_t = std::array<data_t, 3>; // (Ex, Ey, Ez)

  data_t theta(data_t x);
  data_t dirac_delta(data_t x, data_t disc_delta);
  data_t dirac_delta_prime(data_t x, data_t disc_delta);

  void getElectricDipoleWeightingField(point_t& eval_point, field_t& weighting_field, data_t disc_delta);

}

#endif
