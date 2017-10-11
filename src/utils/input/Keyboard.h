#pragma once

#include <map>

class Keyboard
{
private:
	static std::map<int, bool> _keyStatus;
	Keyboard() {}
	~Keyboard() {}
public:
	static void key_callback(int, int);
	static bool isKeyDown(int key);
};
