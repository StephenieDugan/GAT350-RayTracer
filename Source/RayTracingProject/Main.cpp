#include <iostream>
#include "Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";

	Renderer renderer = Renderer();
	renderer.Init();
	renderer.CreateWindow("window", 400, 300);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}
