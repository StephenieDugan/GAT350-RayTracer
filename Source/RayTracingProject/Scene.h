#pragma once
#include "Color.h"
#include "iostream"
#include "Camera.h"
#include "Object.h"
#include "vector"

class Scene
{
public:
	Scene();
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas, int numSamples, int depth);
	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	std::shared_ptr<Camera> m_camera;
	color3_t m_topColor{ 0, 0, 0 };
	color3_t m_bottomColor{ 1, 1, 1 };
	std::vector<std::unique_ptr<Object>> m_objects;
};