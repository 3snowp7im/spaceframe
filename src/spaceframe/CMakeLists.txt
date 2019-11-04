add_executable(spaceframe
  spaceframe.cc
  shader.cc
)

target_include_directories(sf
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(glew REQUIRED glew)

target_link_libraries(spaceframe
  PUBLIC sf sf_glfw3 sf_gmp sf_mpfr sf_spdlog ${glew_LIBRARIES}
)
