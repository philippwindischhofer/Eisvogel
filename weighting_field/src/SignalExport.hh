#ifndef SIGNAL_EXPORT_HH
#define SIGNAL_EXPORT_HH

#include <vector>
#include "Types.hh"

namespace T = Types;

void ExportSignal(std::vector<T::data_t> signal_times, std::vector<T::data_t> signal_values,
		  std::string outpath, int time_prec = 3, int value_prec = 15);

#endif
