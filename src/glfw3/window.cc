#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <sf/log.h>
#include "../spaceframe/window.h"

void spaceframe::window::create(unsigned width, unsigned height, const std::string& title) {
  if (impl != nullptr) {
    throw std::runtime_error("Window already created");
  }
  static bool initialized = false;
  sf::log::debug("Initializing GLFW");
  if (!initialized) {
    if (!glfwInit()) {
      throw std::runtime_error("Could not initialize windowing library");
    }
    initialized = true;
  }
  sf::log::debug("Enabling OpenGL 3.3");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  sf::log::debug("Creating window");
  GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Could not create window");
  }
  glfwMakeContextCurrent(window);
  sf::log::debug("Initalizing GLEW");
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Could not initialize graphics extensions library");
  }
  impl.reset(window);
}

void spaceframe::window::destroy() {
  impl.reset(nullptr);
}

void spaceframe::window::release(void*) {
  if (impl != nullptr) {
    glfwDestroyWindow(static_cast<GLFWwindow*>(impl.get()));
  }
  glfwTerminate();
}

void spaceframe::window::poll_events() {
  glfwPollEvents();
}

bool spaceframe::window::should_close() {
  return !!glfwWindowShouldClose(static_cast<GLFWwindow*>(impl.get()));
}

void spaceframe::window::swap_buffers() {
  glfwSwapBuffers(static_cast<GLFWwindow*>(impl.get()));
}

std::unique_ptr<void, decltype(&spaceframe::window::release)> spaceframe::window::impl = std::unique_ptr<void, decltype(&spaceframe::window::release)>(nullptr, spaceframe::window::release);
