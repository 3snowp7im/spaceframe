#version 330 core

layout(location = 0) in ivec3 vert_pos;
layout(location = 1) in vec3 vert_color;

out vec3 frag_color;

uniform float scale;
uniform mat4 transform;
uniform vec3 origin;
uniform vec3 offset;
uniform mat4 mvp;

void main(){
  vec3 pos = (transform * vec4(vert_pos * scale, 1)).xyz;
  /*
  vec3 adjusted_pos = pos + origin;
  vec3 spherized_pos = adjusted_pos * (adjusted_pos.z / length(adjusted_pos));
  vec3 delta = adjusted_pos - spherized_pos;
  pos -= delta;
  */
  /*gl_Position = mvp * vec4(pos * scale - offset, 1);*/
  gl_Position = mvp * vec4(pos, 1);
  frag_color = vert_color;
}
