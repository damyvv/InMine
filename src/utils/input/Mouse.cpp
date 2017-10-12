#include "Mouse.h"

#include <iostream>

void Mouse::mouse_pos_callback(int posX, int posY) {
	_posX = posX;
	_posY = posY;
}

void Mouse::mouse_rel_callback(int dX, int dY) {
	_dX += dX;
	_dY += dY;
}

void Mouse::reset() {
	_dX = _dY = 0;
}

void Mouse::mouse_button_callback(int button, bool state) {
	_buttonStatus[button] = state;
}

int Mouse::_posX = 0;
int Mouse::_posY = 0;
int Mouse::_dX = 0;
int Mouse::_dY = 0;

std::map<int, bool> Mouse::_buttonStatus = std::map<int, bool>();