#include <algorithm>
#include <cmath>
#include <geom.h>
#include <limits>

// --- Functions ---

vec3 saturate(const vec3 &v) { return max(min(v, 1.0f), 0.0f); }

mat3 rotationFromTo(const vec3 &from, const vec3 &to) {
    vec3 a = normalize(from);
    vec3 b = normalize(to);
    vec3 axis = cross(a, b); // Rotation axis.
    float c = dot(a, b);     // Cosine between vectors.

    // Derivation:
    // https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724
    float k = 1.0f / (1.0f + c);

    mat3 rot =
        mat3((axis.x * axis.x * k) + c, (axis.y * axis.x * k) - axis.z,
             (axis.z * axis.x * k) + axis.y, (axis.x * axis.y * k) + axis.z,
             (axis.y * axis.y * k) + c, (axis.z * axis.y * k) - axis.x,
             (axis.x * axis.z * k) - axis.y, (axis.y * axis.z * k) + axis.x,
             (axis.z * axis.z * k) + c);
    return transpose(rot);
}

// --- Ray ---

Ray::Ray(const vec3 &origin, const vec3 &dir)
    : origin(origin), dir(normalize(dir)) {}

// --- Hit ---

Hit::Hit(float t, const vec3 &point, const vec3 &normal, const vec3 &diffuse)
    : t(t), point(point), normal(normal), diffuse(diffuse) {}

const Hit Hit::NO_HIT =
    Hit(std::numeric_limits<float>::max(), vec3(0), vec3(0), vec3(0));