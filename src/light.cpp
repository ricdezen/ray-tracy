#include <algorithm>
#include <light.h>

vec3 estimateRadiance(const Scene &scene, const Ray &ray) {
    Hit hit = Hit::NO_HIT;
    if (scene.hit(ray, hit, 0, 100000000)) {
        // Material.
        vec3 diffuse = vec3(1, 0, 0);
        vec3 specular = vec3(1, 1, 1);
        float power = 100;

        // Directional light from above.
        vec3 L = vec3(0, 1, 0);
        vec3 R = reflect(-L, hit.normal);

        float NdotL = std::max(dot(hit.normal, vec3(0, 1, 0)), 0.0f);
        float VdotR = std::max(dot(-ray.dir, R), 0.0f);

        return diffuse * NdotL + specular * pow(VdotR, power);
    } else
        return vec3(0.9, 1, 1);
}