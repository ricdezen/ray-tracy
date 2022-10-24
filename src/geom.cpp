#include <algorithm>
#include <cmath>
#include <geom.h>
#include <limits>

// --- Functions ---

vec3 saturate(const vec3 &v) { return max(min(v, 1.0f), 0.0f); }

// --- Ray ---

Ray::Ray(const vec3 &origin, const vec3 &dir)
    : origin(origin), dir(normalize(dir)) {}

// --- Hit ---

Hit::Hit(float t, const vec3 &point, const vec3 &normal)
    : t(t), point(point), normal(normal) {}

const Hit Hit::NO_HIT =
    Hit(std::numeric_limits<float>::max(), vec3(0), vec3(0));

// --- Functions ---

vec3 reflect(const vec3 &incident, const vec3 &normal) {
    return incident - normal * 2.0f * dot(incident, normal);
}