#version 330 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){
  gl_Position = MVP * vertexPosition;

  fragmentColor = vertexColor;
}
