#include <iostream>

#include "Types.hh"
#include "WeightingFieldProvider.hh"
#include "Integrator.hh"

namespace WFP = WeightingFieldProvider;
namespace INT = Integrator;
namespace T = Types;

int main(void) {
  std::cout << "linear test" << std::endl;

  // T::point_4d_t tp = {1.0, 3.0, 3.0, 3.0};
  // T::point_4d_t tp2 = {1.0, 2.0, 3.0, 4.0};
  // T::point_4d_t res = {0.0, 0.0, 0.0, 0.0};

  // T::add<T::data_t>(tp, tp2, res);

  // std::cout << std::to_string(res[0]) << ", " << std::to_string(res[1]) << ", " << std::to_string(res[2]) << ", " << 
  //   std::to_string(res[3]) << std::endl;

  // T::point_4d_t res2 = T::mul(tp, 12.3);

  // std::cout << std::to_string(res2[0]) << ", " << std::to_string(res2[1]) << ", " << std::to_string(res2[2]) << ", " << 
  //   std::to_string(res2[3]) << std::endl;

  // // T::field_t tf = {1.0, 1.0, 1.0};

  // example shower trajectory
  // std::vector<T::point_4d_t> trajectory = {tp, tp, tp};


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
  std::vector<T::data_t> signal;

  auto weighting_field = [](T::data_t t, T::point_3d_t& p, T::field_t& f) -> void {WFP::getElectricDipoleWeightingField(t, p, f, 1.0);};

  INT::convolve(0.0, trajectory, velocity, charge, weighting_field);
  
}
