#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"

int main(int argc, char* argv[])
{
    seedRandom(static_cast<unsigned int>(time(nullptr)));
    std::cout << "Hello world!\n";
    Renderer renderer = Renderer();
    renderer.Init();
    renderer.CreateWindow("window", 400, 300);

    Canvas canvas(400, 300, renderer);

    float aspectRatio = (canvas.GetSize().x / (float)canvas.GetSize().y);

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 3, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    Scene scene(8,glm::vec3{1.0f}, glm::vec3{0.5f,0.7f,1.0f});
    scene.SetCamera(camera);

    auto material = std::make_shared<Lambertian>(color3_t{ 0.8f, 0.0f, 0.0f });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));


    for (int x = -10; x < 1; x++)
    {
        for (int z = -10; z < 1; z++)
        {

            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            //material = std::make_shared<Lambertian>(color3_t{0.0f, 1.0f, 0.0f});

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }


    bool isOld = false;
    if (!isOld) {
        canvas.Clear({ 0,0,0,1 });
        scene.Render(canvas, 4);
        canvas.Update();
    }

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
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
        if (isOld) {
            canvas.Clear({ 0,0,0,1 });
            scene.Render(canvas);
            canvas.Update();
        }

        renderer.PresentCanvas(canvas);
    }
    renderer.Shutdown();

    return 0;
}