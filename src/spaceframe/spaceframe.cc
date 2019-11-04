#include <array>
#include <chrono>
#include <fstream>
#include <GL/glew.h>
#include <sf/sf.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "window.h"
#include "../sf/geom.h"
#include "../sf/log.h"
#include "../sf/mat4.h"
#include "../sf/mpf.h"
#include "../sf/spheroid.h"

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
  sf::log::info("Compiling shader: %s", vertex_file_path.c_str());
  const char* VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
    sf::log::error("%s", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  sf::log::info("Compiling shader: %s", fragment_file_path.c_str());
  const char* FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
    sf::log::error("%s", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  sf::log::debug("Linking program");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    sf::log::error("%s", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}

int main(int argc, char** argv) {
  sf::init();
  auto radius = 1l << 16;

  auto lod = 0;
  sf::geom geom(lod);
  const auto verts = geom.get_verts();
  const auto indices = geom.get_indices();
  const auto index_counts = geom.get_index_counts();
  sf::log::debug("index count %lu", indices.size());

  //spaceframe::window::create(720, 400, "spaceframe");

  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  // Create and compile our GLSL program from the shaders
  //GLuint programID = LoadShaders("src/spaceframe/vert.glsl", "src/spaceframe/frag.glsl");

  //GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  //const sf::vec3<sf::mpf> camera_position = {0, 0, (sf::mpf(1) << 17) + (sf::mpf(1) << 16)};

  sf::mpf camera_z = {1};
  if (argc > 1) {
    camera_z = sf::mpf(std::string(argv[1]));
  }
  const sf::vec3<sf::mpf> camera_position = {0, 0, camera_z};
  sf::log::debug("camera %s", std::to_string(camera_position).c_str());
  const auto camera_translation = sf::mat4<sf::mpf>::translate(-camera_position);
  const auto camera_projection = sf::mat4<sf::mpf>::project(60 * sf::mpf::pi() / 180, sf::mpf(16) / 9, sf::mpf(1), sf::mpf(1) << 22);

  GLuint vertex_array_id;
  //glGenVertexArrays(1, &vertex_array_id);
  //glBindVertexArray(vertex_array_id);

  std::array<GLuint, 2> buffer_ids;
  //glGenBuffers(buffer_ids.size(), &buffer_ids[0]);

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
    for (int j = 0; j < 3; j++) {
      auto verts = static_cast<std::array<GLfloat, 4>>(sf::vec4<sf::mpf>(sf::spheroid::faces[i].orientation * sf::face::verts[j] * radius));
      std::copy(verts.begin(), verts.end(), curr_vertex);
      curr_vertex += verts.size();
    }
  }
  //glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[0]);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer_data.size(), &vertex_buffer_data[0], GL_STATIC_DRAW);

  using frames_per_millisecond = std::chrono::duration<float, std::ratio<60, 1000>>;
  const auto redraw_target_milliseconds = frames_per_millisecond(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)));
  auto last_draw = std::chrono::time_point<std::chrono::steady_clock>();

  auto start = std::chrono::steady_clock::now();

  while (/*!spaceframe::window::should_close()*/1) {
    //spaceframe::window::poll_events();

    // ...input processing...

    const auto rotation = sf::qtrn::from_axis_angle(
      sf::vec3<sf::mpf>(0, 1, 0),
      0//sf::mpf(-(double)std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 2000)
    );

    const auto v = rotation * camera_position;
    const auto p = sf::spheroid::face_pos_from_point(v);
    const auto u = -rotation * p;

    // if curr_pos != last_pos {
    for (int i = 0; i < 20; i++) {
      const auto vec = sf::spheroid::faces[i].vec_from_face_pos(p);
      geom.sample(vec, [&](const sf::face::range_t& range, sf::face::coord_t len) {
        return range[3] <= radius;
      });
      break;
    }
    // }


    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_draw).count() >= redraw_target_milliseconds.count()) {
      last_draw = now;

      //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // auto curr_color = color_buffer_data.begin();
      // for (int i = 0; i < 20; i++) {
      //   if (sf::spheroid::faces[i].is_point_in_bounds(v)) {
          //const auto vec = sf::spheroid::faces[i].vec_from_face_pos(p);
          //sf::log::debug("face %d", i);
          //sf::log::debug("%s", std::to_string(vec).c_str());

        //   for (int j = 0; j < 3; j++) {
        //     *curr_color++ = .3f;
        //     *curr_color++ = .5f;
        //     *curr_color++ = 1.f;
        //     *curr_color++ = 1.f;
        //   }
        // } else {
        //   for (int j = 0; j < 3; j++) {
        //     *curr_color++ = rgb[i % rgb.size()][0];
        //     *curr_color++ = rgb[i % rgb.size()][1];
        //     *curr_color++ = rgb[i % rgb.size()][2];
        //     *curr_color++ = 1.f;
        //   }
        // }
      // }
      //glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[1]);
      //glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * color_buffer_data.size(), &color_buffer_data[0], GL_STATIC_DRAW);

      // 1st attribute buffer : vertices
      //glEnableVertexAttribArray(0);
      //glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[0]);
      //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
      // 2nd attribute buffer : vertex colors
      //glEnableVertexAttribArray(1);
      //glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[1]);
      //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
      // Draw the triangle !
      //glDrawArrays(GL_TRIANGLES, 0, 3 * 20);
      //glDisableVertexAttribArray(0);

      const auto view = static_cast<std::array<GLfloat, 16>>(camera_projection * camera_translation * sf::mat4<sf::mpf>::rotate(rotation));
      //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &view[0]);

      //glUseProgram(programID);

      return 0;
    }

    //spaceframe::window::swap_buffers();
  }
  return 0;
}
