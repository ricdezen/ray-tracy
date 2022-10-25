#include <camera.h>
#include <functional>
#include <light.h>
#include <threading.h>

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

vec3 Camera::capturePixel(const Scene &scene, int x, int y, Camera::MSAA msaa) {
    int samps = static_cast<int>(msaa);
    // TODO: move out.
    const int mcsamps = 1024;
    const int bounces = 16;

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

Image *Camera::capture(const Scene &scene, Camera::MSAA msaa, int threads) {
    Image *image = new Image(width, height);
    std::vector<std::function<void()>> jobs;
    std::mutex image_mutex;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            jobs.push_back([&, i, j] {
                vec3 color = capturePixel(scene, j, i, msaa);
                int r = (int)round(color.x * 255.0);
                int g = (int)round(color.y * 255.0);
                int b = (int)round(color.z * 255.0);

                image_mutex.lock();
                image->drawPixel(j, i, (255 << 24) + r + (g << 8) + (b << 16));
                printf("Pixel %d / %d\n", i * width + j, width * height);
                image_mutex.unlock();
            });

    // Run in parallel.
    parallelize(jobs, threads);

    // Return image.
    return image;
}