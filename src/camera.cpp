#include <camera.h>
#include <light.h>

Camera::Camera(int width, int height) : width(width), height(height) {
    // TODO: remove this.
    fov = 90.0f; // Vertical fov.
    focus_dist = 1.0f;
    aspect_ratio = width * 1.0f / height;

    height_meters = tan(fov / 2.0f) * focus_dist;
    width_meters = height_meters * aspect_ratio;

    // Grid for image pixels.
    vec3 top_left = vec3(-width_meters / 2, height_meters / 2, -focus_dist);
    vec3 top_right = vec3(width_meters / 2, height_meters / 2, -focus_dist);
    vec3 bottom_left = vec3(-width_meters / 2, -height_meters / 2, -focus_dist);
    image_grid = Grid(top_left, top_right, bottom_left, width, height);
}

vec3 Camera::capture(const Scene &scene, int x, int y, Camera::MSAA msaa) {
    int samps = static_cast<int>(msaa);

    // Make ray that goes through pixel.
    Grid pixel_grid = image_grid.subgrid(x, y, samps, samps);

    vec3 color = vec3(0);
    for (int i = 0; i < samps; i++) {
        for (int j = 0; j < samps; j++) {
            vec3 samp = pixel_grid.cellCenter(i, j);
            vec3 raw_col = estimateRadiance(scene, {vec3(0), samp});
            color += saturate(raw_col);
        }
    }
    color /= samps * samps;

    return color;
}