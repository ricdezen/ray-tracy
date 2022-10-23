#include <algorithm>
#include <light.h>

#define PI 3.141

static vec3 sampleSphere() {
    // TODO: move elsewhere.
    float u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float v = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float phi = acos(2 * u - 1);
    float theta = v * 2 * PI;

    // To cartesian.
    return vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}

vec3 estimateRadiance(const Scene &scene, const Ray &ray, int bounces) {
    Hit hit = Hit::NO_HIT;
    if (scene.hit(ray, hit, 0.0001, 100000000)) {
        // Material.
        // No more bounces, no more light.
        if (bounces == 0)
            return vec3(0);

        // Sample random direction in hemisphere around normal.
        // TODO: samples sphere just to try cause it is easier, not correct tho.
        vec3 target = hit.point + hit.normal + sampleSphere();
        vec3 dir = normalize(target - hit.point);
        float pdf = 0.5 / PI; // 1 / 2PI

        // Light coming from random direction in the scene.
        vec3 light = estimateRadiance(scene, {hit.point, dir}, bounces - 1);
        // TODO: here I pretend the BRDF is constant -> lambertian diffuse.
        // The diffuse color is a red.
        // The result is a bit screwed because the pdf above is
        vec3 reflected =
            light * vec3(0.5, 0, 0) / PI * dot(dir, hit.normal) / pdf;

        return reflected;
    }

    // Sky color.
    return vec3(0.8, 0.9, 1.0);
}