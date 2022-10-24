#ifndef GEOM_H
#define GEOM_H

#include <common.h>

// --- Extra geometric functions ---

/**
 * Clamp between 0 and 1.
 */
vec3 saturate(const vec3 &v);

/**
 * Find rotation matrix that aligns the first vector onto the second one.
 *
 * @param from First vector.
 * @param to Second vector.
 */
mat3 rotationFromTo(const vec3 &from, const vec3 &to);

// --- Geometric classes ---

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

#endif // GEOM_H