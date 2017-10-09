#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

struct VertexData3D
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float texSel;
};