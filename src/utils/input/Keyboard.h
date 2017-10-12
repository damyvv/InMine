#pragma once

#include <map>

class Keyboard
{
public:
	enum KeyStatus {
		KEY_STATE_UNKOWN,
		KEY_UP,
		KEY_PRESS,
		KEY_DOWN,
		KEY_RELEASED,
	};
private:
	static std::map<int, KeyStatus> _keyStatus;
	Keyboard() {}
	~Keyboard() {}
public:
	static void key_callback(int, int);
	static void update();

	static Keyboard::KeyStatus getKeyState(int key);
	static bool isKeyDown(int key);
};
