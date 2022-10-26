#include <cmath>
#include <hittable.h>

// --- Sphere ---

Sphere::Sphere(const vec3 &center, const vec3 &color, float radius)
    : center(center), color(color), radius(radius) {}

bool Sphere::hit(const Ray &ray, Hit &hit, float min_t, float max_t) const {
    vec3 oc = ray.origin - center;
    float L_dir = length(ray.dir);
    float a = L_dir * L_dir;

    float halfb = dot(oc, ray.dir);
    float L_oc = length(oc);
    float L_oc_2 = L_oc * L_oc;
    float c = L_oc_2 - radius * radius;

    float discriminant = halfb * halfb - a * c;
    if (discriminant < 0)
        return false;
    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-halfb - sqrtd) / a;
    if (root < min_t || max_t < root) {
        root = (-halfb + sqrtd) / a;
        if (root < min_t || max_t < root)
            return false;
    }

    hit.t = root;
    hit.point = ray.origin + ray.dir * hit.t;
    hit.normal = (hit.point - center) / radius;
    hit.diffuse = color;

    // Flip normal if the ray hit inside the sphere.
    if (dot(hit.normal, ray.dir) > 0)
        hit.normal = -hit.normal;

    return true;
}

// --- Scene ---

Scene::Scene(const std::vector<Sphere> &spheres) : spheres(spheres) {}

bool Scene::hit(const Ray &ray, Hit &hit, float min_t, float max_t) const {
    // Find closest hit.
    bool some_hit = false;
    hit = Hit::NO_HIT;
    for (size_t i = 0; i < spheres.size(); i++) {
        Hit sph_hit = Hit::NO_HIT;
        if (spheres[i].hit(ray, sph_hit, min_t, max_t) && sph_hit.t < hit.t) {
            some_hit = true;
            hit = sph_hit;
        }
    }

    return some_hit;
}