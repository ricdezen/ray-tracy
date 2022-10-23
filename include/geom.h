#ifndef GEOM_H
#define GEOM_H

/**
 * Vector of 3 floats.
 */
struct vec3 {
    float x;
    float y;
    float z;

    vec3() = default;
    vec3(float v);
    vec3(float x, float y, float z);

    // Unary -
    vec3 operator-() const;

    // In-place operators
    vec3 &operator+=(const vec3 &other);
    vec3 &operator-=(const vec3 &other);
    vec3 &operator*=(const vec3 &other);
    vec3 &operator*=(float a);
    vec3 &operator/=(float a);

    // Binary operators
    friend vec3 operator+(vec3 lhs, const vec3 &rhs);
    friend vec3 operator-(vec3 lhs, const vec3 &rhs);
    friend vec3 operator*(vec3 lhs, const vec3 &rhs);
    friend vec3 operator*(vec3 lhs, float rhs);
    friend vec3 operator/(vec3 lhs, float rhs);

    friend float dot(const vec3 &lhs, const vec3 &rhs);
    friend float length(const vec3 &v);
    friend vec3 normalize(const vec3 &v);
    friend vec3 saturate(const vec3 &v);
};

/**
 * Line starting from a point and going in some direction.
 * Constructor ensures direction is normalized.
 */
struct Ray {
    Ray(const vec3 &origin, const vec3 &dir);
    vec3 origin;
    vec3 dir;
};

/**
 * Surface hit. Contains the point and a normal.
 */
struct Hit {
    static const Hit NO_HIT;

    Hit(float t, const vec3 &point, const vec3 &normal);
    float t;
    vec3 point;
    vec3 normal;
};

vec3 reflect(const vec3 &incident, const vec3 &normal);

#endif // GEOM_H