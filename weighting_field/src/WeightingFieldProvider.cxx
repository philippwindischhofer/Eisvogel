#include "WeightingFieldProvider.hh"

#include <iostream>
#include <cmath>

namespace WeightingFieldProvider {

  T::data_t theta(T::data_t x) {
    return x > 0 ? 1.0 : 0.0;
  }

  T::data_t dirac_delta(T::data_t x, T::data_t disc_delta) {
    return std::abs(x) < disc_delta ? 0.5 / disc_delta : 0.0;
  }

  T::data_t dirac_delta_prime(T::data_t x, T::data_t disc_delta) {
    return std::abs(x) < disc_delta ? std::copysign(1.0, x) / std::pow(disc_delta, 2) : 0.0;
  }

  void getElectricDipoleWeightingField(T::data_t eval_t, T::point_3d_t& eval_point, T::field_t& weighting_field, 
				       T::data_t disc_delta) {

    // some constants ... need to be defined elsewhere in the longer term
    T::data_t Qw = 1.0;
    T::data_t eps0 = 1.0;
    T::data_t n = 1.0;
    T::data_t ds = 1.0;
    T::data_t c = 1.0;

    T::data_t t = eval_t;
    T::data_t x = eval_point[0];
    T::data_t y = eval_point[1];
    T::data_t z = eval_point[2];

    T::data_t r_xy = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    T::data_t r = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    T::data_t cos_theta = z / r;
    T::data_t sin_theta = std::sqrt(1.0 - std::pow(cos_theta, 2));
    T::data_t cos_phi = x / r_xy;
    T::data_t sin_phi = y / r_xy;

    T::data_t t_prop = r * n / c;
    T::data_t t_del = t - t_prop;

    T::data_t E_theta = -Qw * ds / (eps0 * 4 * M_PI) * sin_theta / std::pow(r, 3) * (
										  theta(t_del)
										  + t_prop * dirac_delta(t_del, disc_delta)
										  + std::pow(t_prop, 2) * dirac_delta_prime(t_prop, disc_delta)
										  );
    T::data_t E_r = -2.0 * Qw * ds / (eps0 * 4 * M_PI) * cos_theta / std::pow(r, 3) * (
										    theta(t_del)
										    + t_prop * dirac_delta(t_del, disc_delta)
										    );
    
    T::data_t E_x = cos_phi * (E_theta * cos_theta + E_r * sin_theta);
    T::data_t E_y = sin_phi * (E_theta * cos_theta + E_r * sin_theta);
    T::data_t E_z = E_r * cos_theta - E_theta * sin_theta;

    weighting_field[0] = E_x;
    weighting_field[1] = E_y;
    weighting_field[2] = E_z;
  }
}
