#include "Integrator.hh"

#include <iostream>
#include <assert.h>

namespace Integrator {

  T::data_t convolve(T::data_t signal_t, 
		     std::vector<T::point_4d_t>& trajectory, std::vector<T::vector_t>& velocity, std::vector<T::data_t>& charge,
		     std::function<void(T::data_t, T::point_3d_t&, T::field_t&)> weighting_field) {

    // everything needs to have the same length
    assert(trajectory.size() == velocity.size());
    assert(trajectory.size() == charge.size());
    
    int num_interp_points = 10;
    T::data_t interpolation_inc = 1.0 / num_interp_points;

    T::field_t cur_wf = {0.0, 0.0, 0.0};
    T::point_3d_t cur_pt = {0.0, 0.0, 0.0};
    T::data_t signal = 0;

    // interpolate trajectory onto finer grid
    std::vector<T::point_4d_t> trajectory_interpolated;
    std::vector<T::vector_t> velocity_interpolated;
    std::vector<T::data_t> charge_interpolated;

    for(int ind = 0; ind < trajectory.size() - 1; ind++) {      
      for(int step = 0; step < num_interp_points; step++) {
	
	T::data_t lambda = (T::data_t)step / num_interp_points;	
	T::point_4d_t cur_pt = T::add(T::mul(trajectory[ind], 1 - lambda), T::mul(trajectory[ind + 1], lambda));
	T::vector_t cur_velocity = T::add(T::mul(velocity[ind], 1 - lambda), T::mul(velocity[ind + 1], lambda));
	T::data_t cur_charge = charge[ind] * (1 - lambda) + charge[ind + 1] * lambda;

	trajectory_interpolated.push_back(cur_pt);
	velocity_interpolated.push_back(cur_velocity);
	charge_interpolated.push_back(cur_charge);
      }
    }

    trajectory_interpolated.push_back(trajectory.back());
    velocity_interpolated.push_back(velocity.back());
    charge_interpolated.push_back(charge.back());

    // after the interpolation, the integrand is piecewise linear
    // to first order, can now simply run trapezoidal integration in between subsequent points

    return signal;

  }
}
