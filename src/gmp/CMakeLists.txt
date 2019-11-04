add_library(sf_gmp mpz.cc)

target_include_directories(sf_gmp
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(sf_gmp PUBLIC -lgmp)
