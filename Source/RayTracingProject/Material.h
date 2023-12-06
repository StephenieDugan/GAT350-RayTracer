#pragma once
#include "Ray.h"
#include "Color.h"
#include "random.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;
	virtual color3_t GetEmissive() const { return { 0, 0, 0 }; }
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : m_albedo{ albedo } {}
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;

protected:
	color3_t m_albedo;
};

class Metal : public Material {
public:
	Metal(const color3_t& albedo, float fuzziness) : m_albedo(albedo), m_fuzziness(fuzziness) {}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const override;

private:
	color3_t m_albedo;
	float m_fuzziness;
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float index) : m_albedo{ albedo }, m_index{ index } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo;
	float m_index; // refraction index
};
class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity = 1.0f) : m_albedo{ albedo }, m_intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override { return false; }
	color3_t GetEmissive() const override { return  m_intensity * m_albedo; }

private:
	glm::vec3 m_albedo;
	float m_intensity;
};
