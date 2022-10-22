#ifndef CAMERA_H
#define CAMERA_H

#include <geom.h>
#include <hittable.h>

class Camera {
  public:
    /**
     * @param width Width of the resolution, in pixels.
     * @param height Height of the resolution, in pixels.
     */
    Camera(int width, int height);

    /**
     * Capture color for a single pixel.
     */
    vec3 capture(const Scene &scene, int x, int y);

  private:
    int width;
    int height;
    float fov;
    float focus_dist;
    float aspect_ratio;
    float width_meters;
    float height_meters;
    float pixel_size;
};

#endif