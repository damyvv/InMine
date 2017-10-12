#pragma once

#include <map>

class Mouse
{
private:
	static int _posX, _posY, _dX, _dY;
	static std::map<int, bool> _buttonStatus;
	Mouse() {}
	~Mouse() {}
public:
	static void mouse_pos_callback(int posX, int posY);
	static void mouse_rel_callback(int dX, int dY);
	static void mouse_button_callback(int button, bool state);
	static void reset();
	static bool isButtonPressed(int button) { return _buttonStatus[button] != 0; }

	static int getPosX() { return _posX; }
	static int getPosY() { return _posY; }
	static int getDX() { return _dX; }
	static int getDY() { return _dY; }
};