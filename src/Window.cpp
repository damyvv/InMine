#include "Window.h"

#include <exception>

Window::Window(unsigned int width, unsigned int height, bool fullscreen, std::string title) : 
		m_Width(width), 
		m_Height(height), 
		m_Fullscreen(fullscreen), 
		m_Title(title),
		m_IsOpen(false) {

	if (!glfwInit()) {
		throw std::exception("Failed to initialize GLFW");
	}

	m_Window = glfwCreateWindow(800, 600, m_Title.c_str(), NULL, NULL);
	if (!m_Window) {
		throw std::exception("Failed to create a GLFW window");
	}

	glfwMakeContextCurrent(m_Window);
	m_IsOpen = true;

	int result = glewInit();
	if (result) {
		throw std::exception("Fatal error! Unexpected result from glewInit()");
	}

}

Window::~Window() {
	glfwTerminate();
}

void Window::update() {
	m_IsOpen &= !glfwWindowShouldClose(m_Window);

	glfwSwapBuffers(m_Window);

	glfwPollEvents();
}