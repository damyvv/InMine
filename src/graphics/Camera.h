#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	glm::vec3 position, rotation;
public:
	Camera() : position(0), rotation(0) {}
	~Camera() {}

	glm::mat4 getViewMatrix();
};