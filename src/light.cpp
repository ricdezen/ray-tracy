#include <algorithm>
#include <light.h>

static vec3 sampleHemiSphere(const vec3 &normal) {
    // TODO: move elsewhere.
    float u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float v = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float phi = acos(u);
    float theta = v * 2.0f * MY_PIf;

    // To cartesian.
    vec3 L = vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));

    // To world frame.
    mat3 rot = rotationFromTo(vec3(0, 0, 1), normal);

    return rot * L;
}

vec3 estimateRadiance(const Scene &scene, const Ray &ray, int bounces) {
    Hit hit = Hit::NO_HIT;
    if (scene.hit(ray, hit, 0.0001f, 100000000.0f)) {
        // Material.
        // No more bounces, no more light.
        if (bounces == 0)
            return vec3(0);

        // Sample random direction in hemisphere around normal.
        vec3 dir = sampleHemiSphere(hit.normal);
        float pdf = 0.5f / MY_PIf; // 1 / 2PI

        // Light coming from random direction in the scene.
        vec3 light = estimateRadiance(scene, {hit.point, dir}, bounces - 1);
        vec3 color = vec3(1, 0, 0);

        // TODO: here I pretend the BRDF is constant -> lambertian diffuse.
        float NdotL = glm::max(dot(dir, hit.normal), 0.0f);

        return light * hit.diffuse / MY_PIf * NdotL / pdf;
    }

    // Sky color weighted by y component.
    return ray.dir.y * vec3(0.8, 0.9, 1.0);
}