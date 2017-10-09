#include "Window.h"

#include "../utils/input/Keyboard.h"

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
		SDL_DestroyWindow(m_Window);
	}

	int result = glewInit();
	if (result != GLEW_OK) {
		m_Error = "Fatal error! Unexpected result from glewInit()";
		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyWindow(m_Window);
		return;
	}

	m_IsOpen = true;
}

Window::~Window() {
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Window::update() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_IsOpen = false;
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			Keyboard::key_callback(e.key.keysym.sym, e.key.state);
		}
	}
	SDL_GL_SwapWindow(m_Window);
}