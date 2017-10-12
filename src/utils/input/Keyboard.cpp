#include "Keyboard.h"

#include <iostream>
#include <SDL.h>

void Keyboard::key_callback(int key, int action) {
	_keyStatus[key] = (KeyStatus) ((~action & 1) * 2 + 2);
}

void Keyboard::update() {
	for (auto it = _keyStatus.begin(); it != _keyStatus.end(); it++) {
		if (it->second == KEY_PRESS)
			it->second = KEY_DOWN;
		else if (it->second == KEY_RELEASED)
			it->second = KEY_UP;
	}
}

Keyboard::KeyStatus Keyboard::getKeyState(int key) {
	return _keyStatus[key];
}

bool Keyboard::isKeyDown(int key) {
	return _keyStatus[key] == KEY_DOWN;
}

std::map<int, Keyboard::KeyStatus> Keyboard::_keyStatus = std::map<int, Keyboard::KeyStatus>();