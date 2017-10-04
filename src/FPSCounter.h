#pragma once

#include <ctime>
#include <iostream>

class FPSCounter
{
private:
	clock_t m_Start;
	uint16_t m_Frames;
public:
	FPSCounter() {
		m_Start = clock();
		m_Frames = 0;
	}

	void tick() {
		m_Frames++;
		clock_t now = clock();
		clock_t duration = now - m_Start;
		if ((float)duration / CLOCKS_PER_SEC >= 1.0) {
			std::cout << "FPS: " << m_Frames << std::endl;
			m_Start += 1 * CLOCKS_PER_SEC;
			m_Frames = 0;
		}
	}
};