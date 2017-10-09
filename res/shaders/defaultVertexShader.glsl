#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 uv;
layout(location = 3) in float texSel;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 frag_col;
out vec2 frag_uv;
out float frag_texSel;

void main() {
	frag_col = col;
	frag_uv = uv;
	frag_texSel = texSel;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}