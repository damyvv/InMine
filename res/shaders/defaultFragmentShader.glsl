#version 330

in vec4 frag_col;
in vec2 frag_uv;
in float frag_texSel;

layout(binding=0) uniform sampler2D sideTex;
layout(binding=1) uniform sampler2D bottomTex;
layout(binding=2) uniform sampler2D topTex;

void main() {
	vec4 texCol = vec4(0);
	if (frag_texSel == 0) {
		texCol = texture(sideTex, frag_uv);
	} else if (frag_texSel == 1) {
		texCol = texture(bottomTex, frag_uv);
	} else {
		texCol = texture(topTex, frag_uv);
	}
	
	gl_FragColor = texCol * frag_col;
}