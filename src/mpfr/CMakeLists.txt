add_library(sf_mpfr mpf.cc)

target_include_directories(sf_mpfr
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(sf_mpfr PUBLIC -lmpfr)
