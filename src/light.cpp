#include <algorithm>
#include <light.h>

vec3 estimateRadiance(const Scene &scene, const Ray &ray) {
    Hit hit = Hit::NO_HIT;
    if (scene.hit(ray, hit, 0, 100000000))
        // Directional light from above.
        return vec3(1, 0, 0) * std::max(dot(hit.normal, vec3(0, 1, 0)), 0.0f);
    else
        return vec3(0.9, 1, 1);
}