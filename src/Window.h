#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
	unsigned int m_Width, m_Height;
	bool m_Fullscreen;
	std::string m_Title;
	GLFWwindow *m_Window;
	bool m_IsOpen;
public:
	Window(unsigned int width, unsigned int height, bool fullscreen, std::string title);
	virtual ~Window();

	void update();

	inline bool isOpen() { return m_IsOpen; }
};
