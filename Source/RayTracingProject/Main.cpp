#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <memory>

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
	Scene scene(20); 
	scene.SetCamera(camera);


	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 0 });


	// create objects -> add to scene
	for (int i = 0; i < 100; i++)
	{
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-10,10),random(-10,10), random(-4,-6)}, random(0.1, 1), material);
		scene.AddObject(std::move(sphere));
	}
	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-10,10),random(-10,10), random(-4,-6) }, random(0.1, 1), material);
		scene.AddObject(std::move(sphere));
	}


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
