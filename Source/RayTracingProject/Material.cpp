#include "Material.h"
#include "Random.h"
#include "MathUtils.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
{
    glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - raycastHit.point);

    scattered = { raycastHit.point, direction };
    color = m_albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& attenuation, ray_t& scattered) const {
    glm::vec3 reflected = glm::reflect(glm::normalize(ray.m_direction), hit.normal);
    scattered = ray_t(hit.point, reflected + m_fuzziness * randomInUnitSphere());
    attenuation = m_albedo;

    return glm::dot(scattered.m_direction, hit.normal) > 0;
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.m_direction), raycastHit.normal);
    glm::vec3 refracted;

    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface ( ray -> | -> normal )
    // ray is going out of object (ray direction is facing in the same direction of the surface normal)
    if (glm::dot(ray.m_direction, raycastHit.normal) > 0)
    {
        outNormal = -raycastHit.normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.m_direction, raycastHit.normal) / ray.m_direction.length();
    }
    else
    {
        // ray hits outside of surface ( ray -> | <- normal )
        // ray is going into object (ray direction is facing in the opposite direction of the surface norma)
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.m_direction, raycastHit.normal) / ray.m_direction.length();
    }

    // set the probability of the ray being reflected or refracted
    float reflectProbability = 1.0f;
    if (refract(ray.m_direction, outNormal, ni_over_nt, refracted))
    {
        // use schlick and cosine (angle) to determine if ray is reflected or refracted
        reflectProbability = schlick(cosine, m_index);
    }

    // create reflected or refracted ray
    scattered = (random(0.0f,1.0f) < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };
    color = m_albedo;

    return true;
}
