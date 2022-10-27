#ifndef INTEGRATOR_HH
#define INTEGRATOR_HH

#include <vector>
#include <functional>
#include "Types.hh"

namespace Integrator {

  namespace T = Types;

  

  T::data_t convolve(T::data_t signal_t,
		     std::vector<T::point_4d_t>& trajectory, std::vector<T::vector_t>& velocity, std::vector<T::data_t>& charge,
		     std::function<void(T::data_t, T::point_3d_t&, T::field_t&)> weighting_field);
}

#endif
