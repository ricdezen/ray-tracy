#ifndef CAMERA_H
#define CAMERA_H

#include <geom.h>
#include <hittable.h>
#include <utils.h>

class Camera {
  public:
    // Antialiasing with uniform MSAA.
    enum class MSAA { OFF = 1, X4 = 2, X16 = 4 };

    /**
     * @param width Width of the resolution, in pixels.
     * @param height Height of the resolution, in pixels.
     */
    Camera(int width, int height);

    /**
     * Capture color for a single pixel.
     */
    vec3 capture(const Scene &scene, int x, int y, Camera::MSAA msaa);

  private:
    int width;
    int height;
    float fov;
    float focus_dist;
    float aspect_ratio;
    float width_meters;
    float height_meters;

    Grid image_grid;
};

#endif