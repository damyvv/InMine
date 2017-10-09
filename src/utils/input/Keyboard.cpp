#include "Keyboard.h"

#include <iostream>
#include <SDL.h>

void Keyboard::key_callback(int key, int action) {
	_keyStatus[key] = action & 1;
}

bool Keyboard::isKeyDown(int key) {
	if (_keyStatus[key]) return true;
	return false;
}

std::map<int, bool> Keyboard::_keyStatus = std::map<int, bool>();