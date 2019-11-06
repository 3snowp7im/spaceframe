#version 330 core

layout(location = 0) in vec4 vert_pos;
layout(location = 1) in vec4 vert_color;

out vec4 frag_color;

uniform mat4 mvp;

void main(){
  gl_Position = mvp * vert_pos;
  frag_color = vert_color;
}
