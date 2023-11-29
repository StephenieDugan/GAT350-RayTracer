#pragma once
#include "Color.h"
#include "Canvas.h"
#include "Camera.h"
#include "Ray.h"
class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas);
	color3_t Trace(const ray_t& ray);

	void SetCamera(Camera* camera) { m_camera = camera; }

private:
	Camera* m_camera;

	color3_t m_topColor{ 0,0,0 };
	color3_t m_bottomColor{ 1,1,1 };
};

