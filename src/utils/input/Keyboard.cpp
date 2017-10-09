#include "Keyboard.h"

#include <iostream>

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		_keyStatus[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		_keyStatus[key] = false;
	}
}

bool Keyboard::isKeyDown(int key) {
	if (_keyStatus[key]) return true;
	return false;
}

std::map<int, bool> Keyboard::_keyStatus = std::map<int, bool>();