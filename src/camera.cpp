#include <camera.h>
#include <functional>
#include <light.h>
#include <threading.h>
#include <utils.h>

Camera::Camera(int width, int height) : width(width), height(height) {
    // TODO: camera is currently at origin facing z axis, change to allow
    // generic pos.
    // TODO: remove this.
    fov = 90.0f; // Vertical fov.
    focus_dist = 1.0f;
    aspect_ratio = width * 1.0f / height;

    height_meters = (float)tan(fov / 2.0f) * focus_dist;
    width_meters = height_meters * aspect_ratio;

    // Grid for image pixels.
    vec3 top_left = vec3(-width_meters / 2, height_meters / 2, -focus_dist);
    vec3 top_right = vec3(width_meters / 2, height_meters / 2, -focus_dist);
    vec3 bottom_left = vec3(-width_meters / 2, -height_meters / 2, -focus_dist);
    image_grid = Grid(top_left, top_right, bottom_left, width, height);
}

vec3 Camera::capturePixel(const Scene &scene, int x, int y,
                          const RenderParams &p) {
    const int samps = static_cast<int>(p.msaa);
    const int mcsamps = p.samples;
    const int bounces = p.bounces;

    // Make ray that goes through pixel.
    Grid pixel_grid = image_grid.subgrid(x, y, samps, samps);

    vec3 color = vec3(0);
    // For each MSAA sample.
    for (int i = 0; i < samps; i++) {
        for (int j = 0; j < samps; j++) {
            vec3 samp = pixel_grid.cellCenter(i, j);
            // Monte Carlo samples.
            for (int k = 0; k < mcsamps; k++)
                color += estimateRadiance(scene, {vec3(0), samp}, bounces);
        }
    }
    color /= (float)samps * samps * mcsamps;

    return saturate(color);
}

Image *Camera::capture(const Scene &scene, const RenderParams &p) {
    Image *image = new Image(width, height);
    std::vector<std::function<void()>> jobs;
    std::mutex image_mutex;
    int done = 0;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            jobs.push_back([&, i, j] {
                vec3 color = capturePixel(scene, j, i, p);

                // TODO: move this check somewhere else.
                // This is a last resort or should be like a debug check.
                if (color.x != color.x || color.y != color.y ||
                    color.z != color.z) {
                    printf("NaN!\n");
                    exit(1);
                }

                int r = (int)round(color.x * 255.0);
                int g = (int)round(color.y * 255.0);
                int b = (int)round(color.z * 255.0);

                image_mutex.lock();
                image->drawPixel(j, i, (255 << 24) + r + (g << 8) + (b << 16));
                printProgress(++done * 1.0f / (height * width), 32);
                image_mutex.unlock();
            });

    // Run in parallel.
    parallelize(jobs, p.threads);

    // Return image.
    return image;
}