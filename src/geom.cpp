#include <algorithm>
#include <cmath>
#include <geom.h>
#include <limits>

// --- Functions ---

vec3 saturate(const vec3 &v) { return max(min(v, 1.0f), 0.0f); }

mat3 rotationFromTo(const vec3 &from, const vec3 &to) {
    vec3 a = normalize(from);
    vec3 b = normalize(to);
    vec3 r = cross(a, b); // Rotation axis.
    float c = dot(a, b);  // Cosine between vectors.

    // Protect from NaN, return matrix that inverts a vector.
    if (c < -1 + EPSILON)
        return -mat3(1.0f);

    // Derivation:
    // https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724
    float k = 1.0f / (1.0f + c);

    mat3 rot =
        mat3((r.x * r.x * k) + c, (r.y * r.x * k) - r.z, (r.z * r.x * k) + r.y,
             (r.x * r.y * k) + r.z, (r.y * r.y * k) + c, (r.z * r.y * k) - r.x,
             (r.x * r.z * k) - r.y, (r.y * r.z * k) + r.x, (r.z * r.z * k) + c);

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