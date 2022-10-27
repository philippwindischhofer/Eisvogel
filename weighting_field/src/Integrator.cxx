#include "Integrator.hh"

#include <iostream>
#include <assert.h>
#include <numeric>

namespace Integrator {

  T::data_t convolve(T::data_t signal_t, 
		     std::vector<T::point_4d_t>& trajectory, std::vector<T::vector_t>& velocity, std::vector<T::data_t>& charge,
		     std::function<void(const T::data_t, const T::point_3d_t&, T::field_t&)> weighting_field) {

    // some constants
    T::data_t Qw = 1.0;

    // everything needs to have the same length
    assert(trajectory.size() == velocity.size());
    assert(trajectory.size() == charge.size());
    
    int num_interp_points = 10;
    T::data_t interpolation_inc = 1.0 / num_interp_points;

    // interpolate trajectory onto finer grid
    // - - - - - - - - - - - - - - - - - - - - - - 
    // in the real case with a discretised weighting field, need to replace this with the computation of all intersection points
    // of the trajectory segments and the voxel grid
    // - - - - - - - - - - - - - - - - - - - - - - 
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

    // evaluate the integrand at each (interpolated) point
    std::vector<T::data_t> integrand;
    for(int ind = 0; ind < trajectory_interpolated.size(); ind++) {

      T::point_4d_t cur_pt = trajectory_interpolated[ind];
      T::vector_t cur_velocity = velocity_interpolated[ind];
      T::data_t cur_charge = charge_interpolated[ind];
      T::field_t cur_wf;

      // compute weighting field
      weighting_field(signal_t - cur_pt[0], {cur_pt[1], cur_pt[2], cur_pt[3]}, cur_wf);

      // compute integrand
      T::data_t cur_integrand = std::inner_product(cur_wf.begin(), cur_wf.end(), cur_velocity.begin(), 0) / Qw;
      integrand.push_back(cur_integrand);
    }

    // perform the integration
    T::data_t signal = 0;
    for(int ind = 0; ind < integrand.size() - 1; ind++) {
      T::data_t val_l = integrand[ind];
      T::data_t val_r = integrand[ind + 1];
      T::data_t time_l = trajectory[ind][0];
      T::data_t time_r = trajectory[ind + 1][0];

      signal += (val_l + val_r) * (time_r - time_l) / 2;
    }

    return signal;

  }
}
