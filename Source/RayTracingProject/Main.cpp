#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <iostream>
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);

int main(int args, char* argv[])
{
	const int width = 1920/2;
	const int height = 1080/2;
	const int samples = 200;
	const int depth =7 ;
	std::cout << "Hello, World!";
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Init();
	renderer.CreateWindow("winbow", width, height);

	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

	InitScene01(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();

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
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
		renderer.PresentCanvas(canvas);
	}
	// shutdown renderer
	renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 1; x++)
	{
		for (int z = -5; z < 1; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.25f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.5f, 2.5));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.1f, 0.2f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
	for (int x = 0; x < 3; x++)
	{
		for (int z = 0; z < 1; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.25f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.5f, 2.5));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.5f, 0.6f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.25f)));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 5 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 30.0f, aspectRatio);
	scene.SetCamera(camera);

	// Add Cornell Box walls and light source
	auto leftWall = std::make_unique<Plane>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f, 0.3f, 0.3f }));
	auto rightWall = std::make_unique<Plane>(glm::vec3{ 1, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0.3f, 0.8f, 0.3f }));
	auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 0.8f, 0.8f, 0.8f }));
	auto bottomWall = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f, 0.8f, 0.8f }));
	auto lightSource = std::make_unique<Plane>(glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Emissive>(color3_t{ 1, 1, 1 }));

	scene.AddObject(std::move(leftWall));
	scene.AddObject(std::move(rightWall));
	scene.AddObject(std::move(backWall));
	scene.AddObject(std::move(bottomWall));
	scene.AddObject(std::move(lightSource));

	// Add additional objects like triangles and squares with different materials
	float radius = random(0.2f, 0.3f);
	float target = 0;
	auto metalSphere = std::make_unique<Sphere>(glm::vec3{  0.0, radius,  0.0 }, radius, std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.25f)));
	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube-1.obj", glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec3{ 0, 45, 0 }, glm::vec3{ 2.0f,2.0f,2.0f });
	camera->LookAt(glm::vec3{ 0,1,5 }, glm::vec3{ target,0,target }, glm::vec3{ 0,1,0 });
	scene.AddObject(std::move(mesh));
	scene.AddObject(std::move(metalSphere));
	
}