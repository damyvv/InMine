#pragma once

#include <ctime>
#include <iostream>

class FPSCounter
{
private:
	time_t m_Start;
	uint16_t m_Frames;
public:
	FPSCounter() {
		m_Start = time(NULL);
		m_Frames = 0;
	}

	void tick() {
		m_Frames++;
		time_t now = time(NULL);
		time_t duration = now - m_Start;
		if ((float)duration >= 1.0) {
			std::cout << "FPS: " << m_Frames << std::endl;
			m_Start += 1;
			m_Frames = 0;
		}
	}
};