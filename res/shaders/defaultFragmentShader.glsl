#version 330

in vec4 frag_col;
in vec2 frag_uv;

layout(binding=0) uniform sampler2D tex;

void main() {
	gl_FragColor = texture(tex, frag_uv) * frag_col;
}