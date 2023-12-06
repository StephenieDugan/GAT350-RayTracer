#pragma once

#include "Ray.h"
#include "Color.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const color3_t& albedo) : m_albedo(albedo) {}

    virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const override;

private:
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

class Dielectric : public Material {
public:
    Dielectric(const color3_t& albedo, float refractionIndex) : m_albedo(albedo), m_refractionIndex(refractionIndex) {}

    virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const override;

private:
    color3_t m_albedo;
    float m_refractionIndex;
};

class Emissive : public Material {
public:
    Emissive(const color3_t& emissiveColor, float intensity) : m_emissiveColor(emissiveColor), m_intensity(intensity) {}

    virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const override;
private:
    color3_t m_emissiveColor;
    float m_intensity;
};