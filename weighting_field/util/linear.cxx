#include <iostream>

#include "Types.hh"
#include "WeightingFieldProvider.hh"
#include "Integrator.hh"

namespace WFP = WeightingFieldProvider;
namespace INT = Integrator;
namespace T = Types;

int main(void) {
  std::cout << "linear test" << std::endl;

  T::point_t tp = {1.0, 3.0, 3.0, 3.0};
  T::field_t tf = {1.0, 1.0, 1.0};

  WFP::getElectricDipoleWeightingField(tp, tf, 1.0);
  std::cout << std::to_string(tf[0]) + ", " << std::to_string(tf[1])+ ", " << std::to_string(tf[2]) << std::endl;

  // example shower trajectory
  std::vector<T::point_t> trajectory = {tp, tp, tp};
  std::vector<T::data_t> charge;
  std::vector<T::data_t> signal;

  auto weighting_field = [](T::point_t& p, T::field_t& f) -> void {WFP::getElectricDipoleWeightingField(p, f, 1.0);};

  INT::convolve(trajectory, charge, signal, weighting_field);
  
}
