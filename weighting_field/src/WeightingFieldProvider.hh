#ifndef WEIGHTING_FIELD_PROVIDER_HH
#define WEIGHTING_FIELD_PROVIDER_HH

#include "Types.hh"

namespace WeightingFieldProvider {

  namespace T = Types;

  T::data_t theta(T::data_t x);
  T::data_t dirac_delta(T::data_t x, T::data_t disc_delta);
  T::data_t dirac_delta_prime(T::data_t x, T::data_t disc_delta);

  void getElectricDipoleWeightingField(T::point_t& eval_point, T::field_t& weighting_field, T::data_t disc_delta);

}

#endif
