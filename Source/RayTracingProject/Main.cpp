#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";

	seedRandom((unsigned int)time(nullptr));

	Renderer renderer = Renderer();
	renderer.Init();
	renderer.CreateWindow("window", 400, 300);
	Canvas canvas(400, 300, renderer);

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 100000; i++) 
		{
			canvas.DrawPoint({ random(0,400),random(0,300)}, {random(0,255),random(0,255),random(0,255), 1});
		}
		canvas.Update();

		renderer.PresentCanvas(canvas);

		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}
