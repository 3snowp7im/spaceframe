add_library(sf
  face.cc
  geom.cc
  qtrn.cc
  sf.cc
  spheroid.cc
)

target_include_directories(sf
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(sf PUBLIC sf_spdlog -lm)
