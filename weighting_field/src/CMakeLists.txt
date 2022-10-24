add_library(weighting_field WeightingFieldProvider.cxx Integrator.cxx)

target_include_directories(weighting_field PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))
