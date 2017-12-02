#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 uv;

layout(location = 3) in vec3 offset;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 frag_col;
out vec2 frag_uv;

void main() {
	frag_col = col;
	frag_uv = uv;
    gl_Position = projectionMatrix * viewMatrix * vec4(pos + offset, 1);
}