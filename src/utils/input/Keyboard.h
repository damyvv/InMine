#pragma once

//#include <GLFW/glfw3.h>
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
