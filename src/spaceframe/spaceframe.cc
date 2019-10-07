#include <chrono>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include <GL/glew.h>
#include "../sf/mat4.h"
#include "../sf/mpf.h"
#include "../sf/mpz.h"
#include "../sf/spheroid.h"
#include "log.h"
#include "window.h"

GLuint LoadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path){
  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()){
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
  } else{
    throw std::runtime_error("Impossible to open " + vertex_file_path);
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open()){
    std::stringstream sstr;
    sstr << FragmentShaderStream.rdbuf();
    FragmentShaderCode = sstr.str();
    FragmentShaderStream.close();
  } else{
    throw std::runtime_error("Impossible to open " + fragment_file_path);
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  spaceframe::log::info("Compiling shader: %s", vertex_file_path.c_str());
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    spaceframe::log::info("%s", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  spaceframe::log::info("Compiling shader: %s", fragment_file_path.c_str());
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    spaceframe::log::info("%s", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  spaceframe::log::debug("Linking program");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    spaceframe::log::debug("%s", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}

int main() {
  sf::spheroid sphere(1<<16);
  spaceframe::window::create(720, 400, "spaceframe");

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("src/spaceframe/vert.glsl", "src/spaceframe/frag.glsl");

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  const sf::vec3 camera_position = {sf::mpf(0), sf::mpf(0), (sf::mpf(1) << 17) + (sf::mpf(1) << 16)};
  const auto camera_translation = sf::mat4::translate(-camera_position);
  const auto camera_projection = sf::mat4::project(60 * sf::mpf::pi() / 180, sf::mpf(16) / 9, sf::mpf(1), sf::mpf(1) << 22);

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  std::array<GLuint, 2> buffer_ids;
  glGenBuffers(buffer_ids.size(), &buffer_ids[0]);

  std::array<std::array<GLfloat, 3>, 8> rgb = {{
    {1.f, 0.f, 0.f},
    {0.f, 1.f, 0.f},
    {0.f, 0.f, 1.f},
    {1.f, 1.f, 0.f},
    {1.f, 0.f, 1.f},
    {0.f, 1.f, 1.f},
    {1.f, 1.f, 1.f},
    {0.f, 0.f, 0.f},
  }};
  std::array<GLfloat, 3 * 4 * 20> vertex_buffer_data;
  std::array<GLfloat, 3 * 4 * 20> color_buffer_data;

  auto curr_vertex = vertex_buffer_data.begin();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < sf::tetra::face_vertices.size(); j++) {
      auto vertices = static_cast<std::array<GLfloat, 4>>(sf::vec4(sphere.tetras[i].orientation * sf::tetra::face_vertices[j] * sphere.r));
      std::copy(vertices.begin(), vertices.end(), curr_vertex);
      curr_vertex += vertices.size();
    }
  }
  glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer_data.size(), &vertex_buffer_data[0], GL_STATIC_DRAW);

  using frames_per_millisecond = std::chrono::duration<float, std::ratio<60, 1000>>;
  const auto redraw_target_milliseconds = frames_per_millisecond(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)));
  auto last_draw = std::chrono::time_point<std::chrono::steady_clock>();

  auto start = std::chrono::steady_clock::now();

  while (!spaceframe::window::should_close()) {
    spaceframe::window::poll_events();

    // ...input processing...

    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_draw).count() >= redraw_target_milliseconds.count()) {
      last_draw = now;

      glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      const auto rotation = sf::qtrn::from_axis_angle(
        sf::vec3(0, 1, 0),
        sf::mpf(-(double)std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 2000)
      );

      const auto v = rotation * camera_position;
      const auto p = sf::spheroid::point_to_tetra_space(v);

      auto curr_color = color_buffer_data.begin();
      for (int i = 0; i < 20; i++) {
        const auto coords = sf::spheroid::tetras[i].point_to_coords(p);
        if (sf::spheroid::tetras[i].is_point_in_bounds(v)) {
          //spaceframe::log::debug("%02d %lld %lld %lld %lld", i, coords.a, coords.b, coords.c, coords.d);
          for (int j = 0; j < 3; j++) {
            *curr_color++ = .3f;
            *curr_color++ = .5f;
            *curr_color++ = 1.f;
            *curr_color++ = 1.f;
          }
        } else {
          for (int j = 0; j < 3; j++) {
            *curr_color++ = rgb[i % rgb.size()][0];
            *curr_color++ = rgb[i % rgb.size()][1];
            *curr_color++ = rgb[i % rgb.size()][2];
            *curr_color++ = 1.f;
          }
        }
      }
      glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * color_buffer_data.size(), &color_buffer_data[0], GL_STATIC_DRAW);

      // 1st attribute buffer : vertices
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[0]);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
      // 2nd attribute buffer : vertex colors
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[1]);
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
      // Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, 3 * 20);
      glDisableVertexAttribArray(0);

      const auto view = static_cast<std::array<GLfloat, 16>>(camera_projection * camera_translation * sf::mat4::rotate(rotation));
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &view[0]);

      glUseProgram(programID);
    }

    spaceframe::window::swap_buffers();
  }
  return 0;
}
