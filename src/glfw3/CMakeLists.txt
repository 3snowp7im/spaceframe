add_library(sf_glfw3 window.cc)

target_include_directories(sf_glfw3
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(glfw3 REQUIRED glfw3)

target_link_libraries(sf_glfw3 PUBLIC ${glfw3_LIBRARIES})
