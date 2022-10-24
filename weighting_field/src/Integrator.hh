#ifndef INTEGRATOR_HH
#define INTEGRATOR_HH

#include <vector>
#include <functional>
#include "Types.hh"

namespace Integrator {

  namespace T = Types;

  void convolve(std::vector<T::point_t>& trajectory, std::vector<T::data_t>& charge, std::vector<T::data_t>& signal,
		std::function<void(T::point_t&, T::field_t&)> weighting_field);
}

#endif
