#ifndef LIGHT_H
#define LIGHT_H

#include <geom.h>
#include <hittable.h>

/**
 * @param scene The target scene.
 * @param ray A ray to project on the scene.
 */
vec3 estimateRadiance(const Scene &scene, const Ray &ray);

#endif