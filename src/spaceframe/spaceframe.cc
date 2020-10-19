#include <array>
#include <chrono>
#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <sf/log.h>
#include <sf/geom.h>
#include <sf/mat4.h>
#include <sf/sf.h>
#include <sf/spheroid.h>
#include "shader.h"
#include "frag.glsl.h"
#include "vert.glsl.h"
#include "window.h"

using namespace spaceframe;

using geom = sf::geom<GLfloat, 3>;

int main(int argc, char** argv) {
  // Init sf.
  sf::init();
  auto radius = 1l << 16;

  // Create geometry and get references to data.
  auto lod = 1;
  geom geo(lod);
  const auto& verts = geo.get_verts();
  const auto& vert_counts = geo.get_vert_counts();
  const auto& data = geo.get_data();
  const auto& data_counts = geo.get_data_counts();
  const auto& offsets = geo.get_offsets();
  const auto transform = geo.get_transform<GLfloat>();

  // Create window.
  window::create(720, 400, "spaceframe");

  // Enable z-buffer.
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Set a clear color.
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Create and compile our GLSL program from the shaders
  GLuint program_id = load_shaders(
    std::string(reinterpret_cast<char*>(vert_glsl), vert_glsl_len),
    std::string(reinterpret_cast<char*>(frag_glsl), frag_glsl_len)
  );

  // Get uniform locations.
  GLuint scale_uniform_id = glGetUniformLocation(program_id, "scale");
  GLuint transform_uniform_id = glGetUniformLocation(program_id, "transform");
  GLuint origin_uniform_id = glGetUniformLocation(program_id, "origin");
  GLuint offset_uniform_id = glGetUniformLocation(program_id, "offset");
  GLuint mvp_uniform_id = glGetUniformLocation(program_id, "mvp");

  // Set up the camera.
  sf::mpf camera_z(2 * radius);
  if (argc > 1) {
    camera_z = sf::mpf(std::string(argv[1]));
  }
  sf::vec3<sf::mpf> camera_position = {0, 0, camera_z};
  const auto camera_projection = sf::mat4<sf::mpf>::project(60 * sf::mpf::pi() / 180, sf::mpf(16) / 9, sf::mpf(1), sf::mpf(1) << 22);

  // Create the vertex array.
  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  // Generate vertex positions buffer.
  GLuint vert_buffer_id;
  glGenBuffers(1, &vert_buffer_id);

  // Generate vertex data buffer.
  GLuint vert_data_buffer_id;
  glGenBuffers(1, &vert_data_buffer_id);

  // Calculate redraw interval.
  using frames_per_millisecond = std::chrono::duration<float, std::ratio<60, 1000>>;
  const auto redraw_target_milliseconds = frames_per_millisecond(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)));
  auto last_draw = std::chrono::time_point<std::chrono::steady_clock>();
  auto start = std::chrono::steady_clock::now();

  // Main loop.
  while (!window::get_should_close()) {
    // Process input.
    window::poll_events();
    if (window::get_key_state(input::key_t::escape) == input::key_state_t::press) {
      window::set_should_close();
    }
    if (window::get_key_state(input::key_t::space) == input::key_state_t::press) {
      camera_position[2] += 64;
      //sf::log::debug("%s", camera_position[2].to_string().c_str());
    }
    if (window::get_key_state(input::key_t::left_shift) == input::key_state_t::press) {
      camera_position[2] -= 64;
      //sf::log::debug("%s", camera_position[2].to_string().c_str());
    }

    // const auto rotation = sf::qtrn::from_axis_angle(
    //   sf::vec3<sf::mpf>(0, 1, 0),
    //   0//sf::mpf(-(double)std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 2000)
    // );

    // const auto v = rotation * camera_position;
    // const auto p = sf::spheroid::face_pos_from_point(v);
    // const auto u = -rotation * p;

    const auto v = camera_position;
    const auto face_pos = sf::spheroid::face_pos_from_point(v);

    // if curr_pos != last_pos {
    //   for (int i = 0; i < 20; i++) {
    const auto vec = sf::spheroid::faces[0].vec_from_face_pos(face_pos);
    geo.sample(vec, [&](const sf::face::range& range) {
      return range.start[3] <= radius;
    }, [](std::vector<GLfloat>::iterator& iter, const sf::face::range& range) {
      *iter++ = 1.f;
      *iter++ = 0.f;
      *iter++ = 1.f;
    });
    //   }
    // }

    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_draw).count() >= redraw_target_milliseconds.count()) {
      last_draw = now;
      // Clear the drawing buffers.
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glUseProgram(program_id);
      // Enable the vertices position attribute which stays the same for each level of detail.
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vert_buffer_id);
      glVertexAttribIPointer(0, 3, GL_INT, 0, nullptr);
      // Enable the vertex data attribute.
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, vert_data_buffer_id);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
      // Upload the vert transform uniform.
      const auto transform_uniform = static_cast<std::array<GLfloat, 16>>(transform);
      glUniformMatrix4fv(transform_uniform_id, 1, GL_FALSE, &transform_uniform[0]);
      // Upload the origin uniform.
      //const auto origin = sf::face::point_from_vert(sf::face::vert_from_vec(sf::face::coords_from_vec(vec)));
      //const auto origin_uniform = static_cast<std::array<GLfloat, 3>>(orig);
      //glUniform3f(origin_uniform_id, origin[0], origin[1], origin[2]);
      // Upload the view transform uniform.
      sf::log::debug("%s", camera_position.to_string().c_str());
      const auto mvp_uniform = static_cast<std::array<GLfloat, 16>>(camera_projection * sf::mat4<sf::mpf>::translate(-camera_position));
      glUniformMatrix4fv(mvp_uniform_id, 1, GL_FALSE, &mvp_uniform[0]);
      // Draw each level of detail.
      float scale = 1;
      for (int i = 0; i < verts.size(); i++) {
        // Upload the scale uniform.
        glUniform1f(scale_uniform_id, scale);
        // Upload the offset uniform.
        const auto offset = static_cast<std::array<GLfloat, 3>>(offsets[i]);
        glUniform3f(offset_uniform_id, offset[0], offset[1], offset[2]);
        // Upload the vertex positions.
        glBindBuffer(GL_ARRAY_BUFFER, vert_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vert_counts[i], &verts[i][0], GL_DYNAMIC_DRAW);
        // Upload the vertex data.
        glBindBuffer(GL_ARRAY_BUFFER, vert_data_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data_counts[i], &data[i][0], GL_DYNAMIC_DRAW);
        // Draw the level of detail.
        glDrawArrays(GL_TRIANGLES, 0, vert_counts[i] / 3);

        if (vert_counts[i]) {
          sf::log::debug("index: %d", i);
          sf::log::debug("%f", scale);
          sf::log::debug("%f %f %f", offset[0], offset[1], offset[2]);
          for (int j = 0; j < vert_counts[i]; j += 3) {
            sf::log::debug("%d %d %d", verts[i][j + 0], verts[i][j + 1], verts[i][j + 2]);
          }
        }

        scale *= 2;
      }
      exit(0);

      // Disable the attributes.
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
    }

    // Display the buffer.
    window::swap_buffers();
  }
  return 0;
}
