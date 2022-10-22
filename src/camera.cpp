#include <camera.h>

Camera::Camera(int width, int height) : width(width), height(height) {
    // TODO: remove this.
    fov = 90.0; // Vertical fov.
    focus_dist = 1.0;
    aspect_ratio = width * 1.0 / height;

    height_meters = tan(fov / 2.0) * focus_dist;
    width_meters = height_meters * aspect_ratio;

    pixel_size = height_meters / height;
}

vec3 Camera::capture(const Scene &scene, int x, int y) {
    // Make ray that goes through pixel.
    vec3 top_left = vec3(-width_meters / 2, height_meters / 2, -focus_dist);
    vec3 pixel_top_left = top_left + vec3(x * pixel_size, -y * pixel_size, 0);

    vec3 color = vec3(0);
    int samps = 3;
    float subpix_size = pixel_size / samps;
    for (int i = 0; i < samps; i++) {
        for (int j = 0; j < samps; j++) {
            vec3 samp =
                pixel_top_left + vec3(i * subpix_size + subpix_size * 0.5,
                                      -j * subpix_size - subpix_size * 0.5, 0);
            Ray ray = Ray(vec3(0), samp);
            Hit hit = Hit::NO_HIT;
            if (scene.hit(ray, hit, 0, 100000000))
                color += vec3(1, 0, 0);
            else
                color += vec3(0.9, 0.9, 1);
        }
    }
    color /= samps * samps;

    return color;
}