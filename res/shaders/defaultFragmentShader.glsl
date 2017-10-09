#version 330

in vec4 frag_col;
in vec2 frag_uv;

void main() {
    gl_FragColor = vec4(frag_uv, 0, 1);
}