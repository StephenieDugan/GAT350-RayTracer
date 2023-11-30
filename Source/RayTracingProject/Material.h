#pragma once
#include "Ray.h"
#include "Random.h"
#include "Color.h"
#include <glm/glm.hpp>
class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0; 
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : m_albedo{ albedo } {}
	inline bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
	{
		/*glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
		glm::vec3 direction = glm::normalize(target - hit.point);
		scattered = { hit.point, direction };
		attenuation = m_albedo;*/
		color = m_albedo;
		return true;
	}

protected:
	color3_t m_albedo;
};

