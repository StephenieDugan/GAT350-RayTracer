#include "Material.h"
#include "Random.h"
#include <algorithm>
#include <SDL_stdinc.h>

float reflectance(float cosine, float refractionRatio) {
	// Schlick's approximation for reflectance
	float r0 = (1 - refractionRatio) / (1 + refractionRatio);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
glm::vec3 randomUnitVector() {
	float theta = 2.0f * static_cast<float>(M_PI) * random01();
	float phi = acos(2.0f * random01() - 1.0f);

	float x = sin(phi) * cos(theta);
	float y = sin(phi) * sin(theta);
	float z = cos(phi);

	return glm::vec3(x, y, z);
}
bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const {
	glm::vec3 scatterDirection = hit.normal + randomUnitVector();

	// Catch degenerate scatter direction
	if (glm::length(scatterDirection) < 1e-8) {
		scatterDirection = hit.normal;
	}

	scattered = ray_t(hit.point, scatterDirection);
	attenuation = m_albedo;
	return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const {
	glm::vec3 reflected = glm::reflect(glm::normalize(ray.m_direction), hit.normal);
	scattered = ray_t(hit.point, reflected + m_fuzziness * randomInUnitSphere());
	attenuation = m_albedo;

	return glm::dot(scattered.m_direction, hit.normal) > 0;
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const {
	attenuation = m_albedo;
	float refractionRatio = hit.material == this ? (1.0f / m_refractionIndex) : m_refractionIndex;

	glm::vec3 unitDirection = glm::normalize(ray.m_direction);

	float cosTheta = std::min(glm::dot(-unitDirection, hit.normal), 1.0f);
	float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0f;

	glm::vec3 direction;

	if (cannotRefract || reflectance(cosTheta, refractionRatio) > random01()) {
		direction = glm::reflect(unitDirection, hit.normal);
	}
	else {
		direction = glm::refract(unitDirection, hit.normal, refractionRatio);
	}

	scattered = ray_t(hit.point, direction);
	return true;
}

bool Emissive::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const {
	// Emissive materials don't scatter, they emit light
	return false;
}
