#include <iostream>

#include "Types.hh"
#include "WeightingFieldProvider.hh"
#include "Integrator.hh"
#include "SignalExport.hh"

namespace WFP = WeightingFieldProvider;
namespace INT = Integrator;
namespace T = Types;

int main(void) {

  T::data_t start_time = -1000;
  T::data_t end_time = 1000;
  T::data_t x_velocity = 0.9;
  T::data_t z_offset = 1;

  std::vector<T::point_4d_t> trajectory = {
    {start_time, start_time * x_velocity, 0, z_offset},
    {0, 0, 0, z_offset},
    {end_time, end_time * x_velocity, 0, z_offset}
  };
  std::vector<T::vector_t> velocity = {
    {x_velocity, 0, 0},
    {x_velocity, 0, 0},
    {x_velocity, 0, 0}
  };
  std::vector<T::data_t> charge = {
    1, 1, 1
  };

  auto weighting_field = [](const T::data_t t, const T::point_3d_t& p, T::field_t& f) -> void {WFP::getElectricDipoleWeightingField(t, p, f, 0.05);};

  std::vector<T::data_t> signal_times;
  std::vector<T::data_t> signal_values;
  for(T::data_t cur_time = -3; cur_time < 4; cur_time += 0.5) {
    signal_times.push_back(cur_time);
    T::data_t cur_signal = INT::convolve(cur_time, trajectory, velocity, charge, weighting_field);
    signal_values.push_back(cur_signal);
  }  

  ExportSignal(signal_times, signal_values, "./test_signal.csv");
}
