#ifndef CAMERA_H
#define CAMERA_H

#include <display.h>
#include <geom.h>
#include <hittable.h>
#include <utils.h>

struct RenderParams {
    // Antialiasing values.
    enum class MSAA { OFF = 1, X4 = 2, X16 = 4 };

    MSAA msaa;   // Multiple subpixels for each pixel.
    int samples; // Monte Carlo Samples for each subpixel.
    int bounces; // Max bounces for each light ray.
    int threads; // How many concurrent threads.
};

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
    vec3 capturePixel(const Scene &scene, int x, int y, const RenderParams &p);

    /**
     * Capture image from scene.
     *
     * @param scene The scene to capture.
     * @param msaa Antialiasing setting.
     * @param threads How many threads to use.
     */
    Image *capture(const Scene &scene, const RenderParams &p);

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