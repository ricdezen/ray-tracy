#include <algorithm>
#include <cmath>
#include <geom.h>
#include <limits>

// --- vec3 ---

vec3::vec3(float v) : x(v), y(v), z(v) {}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

vec3 vec3::operator-() const { return vec3(-x, -y, -z); }

vec3 &vec3::operator+=(const vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec3 &vec3::operator-=(const vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec3 &vec3::operator*=(const vec3 &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

vec3 &vec3::operator*=(float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

vec3 &vec3::operator/=(float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

vec3 operator+(vec3 lhs, const vec3 &rhs) {
    lhs += rhs;
    return lhs;
}

vec3 operator-(vec3 lhs, const vec3 &rhs) {
    lhs -= rhs;
    return lhs;
}

vec3 operator*(vec3 lhs, float rhs) {
    lhs *= rhs;
    return lhs;
}

vec3 operator*(vec3 lhs, const vec3 &rhs) {
    lhs *= rhs;
    return lhs;
}

vec3 operator/(vec3 lhs, float rhs) {
    lhs /= rhs;
    return lhs;
}

float dot(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float length(const vec3 &v) { return sqrt(dot(v, v)); }

vec3 normalize(const vec3 &v) { return v / length(v); }

vec3 saturate(const vec3 &v) {
    return vec3(std::max(std::min(v.x, 1.0f), 0.0f),
                std::max(std::min(v.y, 1.0f), 0.0f),
                std::max(std::min(v.z, 1.0f), 0.0f));
}

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
    return incident - normal * 2 * dot(incident, normal);
}