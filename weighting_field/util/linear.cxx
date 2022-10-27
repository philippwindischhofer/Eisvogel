#include <iostream>

#include "Types.hh"
#include "WeightingFieldProvider.hh"
#include "Integrator.hh"

namespace WFP = WeightingFieldProvider;
namespace INT = Integrator;
namespace T = Types;

int main(void) {

  std::vector<T::point_4d_t> trajectory = {
    {0, -10, 0, 1},
    {1, 0, 0, 1},
    {2, 10, 0, 1}
  };
  std::vector<T::vector_t> velocity = {
    {10, 0, 0},
    {10, 0, 0},
    {10, 0, 0}
  };
  std::vector<T::data_t> charge = {
    1, 1, 1
  };

  auto weighting_field = [](const T::data_t t, const T::point_3d_t& p, T::field_t& f) -> void {WFP::getElectricDipoleWeightingField(t, p, f, 1.0);};

  T::data_t signal = INT::convolve(0.0, trajectory, velocity, charge, weighting_field);
  std::cout << signal << std::endl;
  
}
