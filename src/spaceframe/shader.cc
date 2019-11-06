#include <stdexcept>
#include <vector>
#include "shader.h"

namespace spaceframe {

  GLuint load_shaders(const std::string& vert_shader, const std::string& frag_shader) {
    // Create the shaders.
    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    GLint res = GL_FALSE;
    int log_size;

    // Compile vertex shader.
    auto vert_shader_source = vert_shader.c_str();
    glShaderSource(vert_shader_id, 1, &vert_shader_source, nullptr);
    glCompileShader(vert_shader_id);

    // Check compile status.
    glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &res);
    glGetShaderiv(vert_shader_id, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 0) {
      std::vector<char> log(log_size + 1);
      glGetShaderInfoLog(vert_shader_id, log_size, nullptr, &log[0]);
      throw std::runtime_error("Error compiling vertex shader: " + std::string(log.begin(), log.end()));
    }

    // Compile fargment shader.
    auto frag_shader_source = frag_shader.c_str();
    glShaderSource(frag_shader_id, 1, &frag_shader_source, nullptr);
    glCompileShader(frag_shader_id);

    // Check compile status.
    glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &res);
    glGetShaderiv(frag_shader_id, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 0) {
      std::vector<char> log(log_size + 1);
      glGetShaderInfoLog(frag_shader_id, log_size, nullptr, &log[0]);
      throw std::runtime_error("Error compiling fragment shader: " + std::string(log.begin(), log.end()));
    }

    // Link the program.
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vert_shader_id);
    glAttachShader(program_id, frag_shader_id);
    glLinkProgram(program_id);

    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &res);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 0) {
      std::vector<char> log(log_size + 1);
      glGetProgramInfoLog(program_id, log_size, NULL, &log[0]);
      throw std::runtime_error("Error linking program: " + std::string(log.begin(), log.end()));
    }

    // Cleanup.
    glDetachShader(program_id, vert_shader_id);
    glDetachShader(program_id, frag_shader_id);

    glDeleteShader(vert_shader_id);
    glDeleteShader(frag_shader_id);

    return program_id;
  }

}
