#pragma once

#include <string>
#include <GL/glew.h>
#include <SDL.h>

class Window {
private:
	unsigned int m_Width, m_Height;
	bool m_Fullscreen;
	std::string m_Title;
	SDL_Window *m_Window;
	SDL_GLContext m_Context;
	bool m_IsOpen;
	std::string m_Error;
public:
	Window(unsigned int width, unsigned int height, bool fullscreen, std::string title);
	virtual ~Window();

	void update();

	inline bool isOpen() const { return m_IsOpen; }
	const std::string& getErrorMessage() const { return m_Error; }

	inline unsigned int getWidth() const { return m_Width; }
	inline unsigned int getHeight() const { return m_Height; }
};
