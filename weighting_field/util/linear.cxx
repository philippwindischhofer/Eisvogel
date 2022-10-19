#include <iostream>

#include "WeightingFieldProvider.hh"

namespace WFP = WeightingFieldProvider;

int main(void) {
  std::cout << "linear test" << std::endl;

  WFP::point_t tp = {1.0, 3.0, 3.0, 3.0};
  WFP::field_t tf = {1.0, 1.0, 1.0};

  WFP::getElectricDipoleWeightingField(tp, tf, 1.0);
  std::cout << std::to_string(tf[0]) + ", " << std::to_string(tf[1])+ ", " << std::to_string(tf[2]) << std::endl;
}
