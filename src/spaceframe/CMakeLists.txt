file(GLOB GENERATED_SHADER_CODE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} vert.glsl frag.glsl)
foreach(INPUT_FILE ${GENERATED_SHADER_CODE})
  string(REPLACE "." "_" VAR_NAME ${INPUT_FILE})
  set(OUTPUT_HEADER_FILE ${INPUT_FILE}.h)
  set(OUTPUT_SOURCE_FILE ${INPUT_FILE}.cc)
  add_custom_command(
    OUTPUT ${OUTPUT_HEADER_FILE} ${OUTPUT_SOURCE_FILE}
    COMMAND printf \"\#pragma once\\nnamespace spaceframe {\\nextern unsigned char ${VAR_NAME}[]\;\\nextern unsigned int ${VAR_NAME}_len\;\\n}\\n\" > ${OUTPUT_HEADER_FILE}
    COMMAND printf \"\#include \\\"${OUTPUT_HEADER_FILE}\\\"\\nnamespace spaceframe {\\n\" > ${OUTPUT_SOURCE_FILE}
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && xxd -i ${INPUT_FILE} >> ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_SOURCE_FILE}
    COMMAND printf \"}\\n\" >> ${OUTPUT_SOURCE_FILE}
    COMMENT "Converting ${INPUT_FILE} to source code"
    DEPENDS ${INPUT_FILE}
  )
  list(APPEND GENERATED_SHADER_CODE ${OUTPUT_SOURCE_FILE})
endforeach()

add_executable(spaceframe
  spaceframe.cc
  shader.cc
  ${GENERATED_SHADER_CODE}
)

target_include_directories(spaceframe
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(glew REQUIRED glew)

target_link_libraries(spaceframe
  PUBLIC sf sf_glfw3 sf_gmp sf_mpfr sf_spdlog ${glew_LIBRARIES}
)
