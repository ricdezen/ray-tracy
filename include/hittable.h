#ifndef HITTABLE_H
#define HITTABLE_H

#include <geom.h>
#include <vector>

/**
 * Base class.
 */
class Hittable {
  public:
    /**
     * @param ray The ray that tries to hit this object.
     * @param hit The output variable for the recorded hit.
     * @return true if the ray hits, false otherwise
     */
    virtual bool hit(const Ray &ray, Hit &hit, float min_t,
                     float max_t) const = 0;
};

/**
 * A Sphere.
 */
class Sphere : Hittable {
  public:
    Sphere(const vec3 &center, float radius);

    bool hit(const Ray &ray, Hit &hit, float min_t, float max_t) const;

  private:
    vec3 center;
    float radius;
};

/**
 * A Scene, essentially a group of Hittables.
 */
class Scene : Hittable {
  public:
    Scene(const std::vector<Sphere> &spheres);

    bool hit(const Ray &ray, Hit &hit, float min_t, float max_t) const;

  private:
    std::vector<Sphere> spheres;
};

#endif