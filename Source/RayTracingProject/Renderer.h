#pragma once

#include <SDL.h>
#include <iostream>
class Renderer
{
public:
	Renderer() = default;

	bool Init();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};

