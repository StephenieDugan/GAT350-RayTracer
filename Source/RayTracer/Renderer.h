#pragma once

#include <string>
class Renderer
{
public:
	Renderer() = default;

	bool Init();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	//SDL_Window* = nullptr;
};

