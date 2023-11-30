#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";

	seedRandom((unsigned int)time(nullptr));

	Renderer renderer = Renderer();
	renderer.Init();
	renderer.CreateWindow("window", 400, 300);
	Canvas canvas(400, 300, renderer);
	float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	Scene scene({ 0.5, 0.5, 0.0 }, { 0.1, 0.3, 0.0 }); 
	scene.SetCamera(camera);
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
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
