#include <iostream>
#include <cmath>

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
  T::data_t z_offset = 10;
  T::data_t z0 = 100; // longitudinal shower scale

  std::vector<T::point_4d_t> trajectory;
  std::vector<T::vector_t> velocity;
  std::vector<T::data_t> charge;

  for(T::data_t cur_time = start_time; cur_time < end_time; cur_time += 0.5) {
    T::point_4d_t cur_point = {cur_time, cur_time * x_velocity, 0, z_offset};
    T::vector_t cur_velocity = {x_velocity, 0, 0};
    T::data_t cur_charge = -std::exp(x_velocity * cur_time / z0);

    trajectory.push_back(cur_point);
    velocity.push_back(cur_velocity);
    charge.push_back(cur_charge);
  }

  auto weighting_field = [](const T::data_t t, const T::point_3d_t& p, T::field_t& f) -> void {WFP::getElectricDipoleWeightingField(t, p, f, 0.05);};

  std::vector<T::data_t> signal_times;
  std::vector<T::data_t> signal_values;
  for(T::data_t cur_time = -15; cur_time < 15; cur_time += 1.0) {
    signal_times.push_back(cur_time);
    T::data_t cur_signal = INT::convolve(cur_time, trajectory, velocity, charge, weighting_field);
    signal_values.push_back(cur_signal);
  }  

  ExportSignal(signal_times, signal_values, "./test_signal.csv");
}
