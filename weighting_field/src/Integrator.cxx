#include "Integrator.hh"

#include <iostream>

namespace Integrator {

  void convolve(std::vector<T::point_t>& trajectory, std::vector<T::data_t>& charge, std::vector<T::data_t>& signal,  
		std::function<void(T::point_t&, T::field_t&)> weighting_field) {
  
    std::cout << "starting to integrate" << std::endl;

    for(auto point: trajectory) {
      T::field_t tf = {1.0, 1.0, 1.0};
      weighting_field(point, tf);

      std::cout << std::to_string(tf[0]) + ", " << std::to_string(tf[1])+ ", " << std::to_string(tf[2]) << std::endl;
    }
  }
}
