#include "Window.h"

Window::Window(unsigned int width, unsigned int height, bool fullscreen, std::string title) : 
		m_Width(width), 
		m_Height(height), 
		m_Fullscreen(fullscreen), 
		m_Title(title),
		m_IsOpen(false) {

	if (!glfwInit()) {
		m_Error = "Failed to initialize GLFW";
		return;
	}

	m_Window = glfwCreateWindow(800, 600, m_Title.c_str(), NULL, NULL);
	if (!m_Window) {
		m_Error = "Failed to create a GLFW window";
		return;
	}

	glfwMakeContextCurrent(m_Window);

	int result = glewInit();
	if (result) {
		m_Error = "Fatal error! Unexpected result from glewInit()";
		glfwDestroyWindow(m_Window);
		return;
	}

	m_IsOpen = true;
}

Window::~Window() {
	glfwTerminate();
}

void Window::update() {
	m_IsOpen &= !glfwWindowShouldClose(m_Window);

	glfwSwapBuffers(m_Window);

	glfwPollEvents();
}