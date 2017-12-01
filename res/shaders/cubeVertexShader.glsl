#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 uv;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(std430, binding=2) buffer OffsetsBlock
{
	float offsets[];
};

out vec4 frag_col;
out vec2 frag_uv;

void main() {
	frag_col = col;
	frag_uv = uv;
	vec3 offset = vec3(offsets[gl_InstanceID * 3], offsets[gl_InstanceID * 3 + 1], offsets[gl_InstanceID * 3 + 2]);
    gl_Position = projectionMatrix * viewMatrix * vec4(pos + offset, 1);
}