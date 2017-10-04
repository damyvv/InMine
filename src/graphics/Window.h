#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	unsigned int m_Width, m_Height;
	bool m_Fullscreen;
	std::string m_Title;
	GLFWwindow *m_Window;
	bool m_IsOpen;
	std::string m_Error;
public:
	Window(unsigned int width, unsigned int height, bool fullscreen, std::string title);
	virtual ~Window();

	void update();

	inline bool isOpen() const { return m_IsOpen; }
	const std::string& getErrorMessage() const { return m_Error; }
};
