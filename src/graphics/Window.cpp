#include "Window.h"

#include "../utils/input/Keyboard.h"
#include "../utils/input/Mouse.h"

Window::Window(unsigned int width, unsigned int height, bool fullscreen, std::string title) : 
		m_Width(width), 
		m_Height(height), 
		m_Fullscreen(fullscreen), 
		m_Title(title),
		m_IsOpen(false) {

	m_Error = "";
	if (SDL_Init(SDL_INIT_VIDEO)) {
		m_Error += "Could not initalize SDL2:\n";
		m_Error += SDL_GetError();
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!m_Window) {
		m_Error += "Failed to create a window:\n";
		m_Error += SDL_GetError();
		return;
	}

	m_Context = SDL_GL_CreateContext(m_Window);
	if (m_Context == NULL) {
		m_Error += "Failed to create OpenGL context:\n";
		m_Error += SDL_GetError();
		return;
	}

	int result = glewInit();
	if (result != GLEW_OK) {
		m_Error = "Fatal error! Unexpected result from glewInit()";
		return;
	}

	m_IsOpen = true;
}

Window::~Window() {
	if (m_Context != NULL)
		SDL_GL_DeleteContext(m_Context);
	if (m_Window)
		SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Window::update() {
	SDL_Event e;
	Keyboard::update();
	Mouse::reset();
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_IsOpen = false;
		}
		else if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0) {
			Keyboard::key_callback(e.key.keysym.sym, e.key.state);
		} 
		else if (e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN) {
			Mouse::mouse_button_callback(e.button.button, e.button.state);
		}
		else if (e.type == SDL_MOUSEMOTION) {
			Mouse::mouse_pos_callback(e.motion.x, e.motion.y);
			Mouse::mouse_rel_callback(e.motion.xrel, e.motion.yrel);
		}
	}
	SDL_GL_SwapWindow(m_Window);
}