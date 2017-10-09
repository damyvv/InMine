#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 m(1);
	m = glm::rotate(m, rotation.x, glm::vec3(1, 0, 0));
	m = glm::rotate(m, rotation.y, glm::vec3(0, 1, 0));
	m = glm::translate(m, position);
	return m;
}