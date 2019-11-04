add_library(sf_spdlog
  log.cc
)

target_include_directories(sf_spdlog
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)

target_link_libraries(sf_spdlog PUBLIC ${CMAKE_THREAD_LIBS_INIT})
