#include <SDL.h>
#include <camera.h>
#include <chrono>
#include <cstdio>
#include <display.h>
#include <hittable.h>
#include <iostream>

namespace chrono = std::chrono;

// If expression does not eval to 0, print SDL error.
#define ERROR_WRAP_SDL(expression)                                             \
    {                                                                          \
        if (expression != 0)                                                   \
            printf(SDL_GetError());                                            \
    }

int main(int argc, char **args) {
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    const int IMG_WIDTH = 1280;
    const int IMG_HEIGHT = 720;

    // Initialize SDL.
    ERROR_WRAP_SDL(SDL_Init(SDL_INIT_EVERYTHING));

    // Make canvas image.
    Image image(IMG_WIDTH, IMG_HEIGHT);

    // Make scene.
    Scene scene({Sphere(vec3(0, 0, -5), 1), Sphere(vec3(-2, 0, -5), 1),
                 Sphere(vec3(2, 0, -5), 1), Sphere(vec3(0, -101, -5), 100)});

    // Make camera.
    Camera camera(IMG_WIDTH, IMG_HEIGHT);

    // Measure time.
    auto start_time = chrono::high_resolution_clock::now();

    // Generate image.
    for (int i = 0; i < IMG_HEIGHT; i++)
        for (int j = 0; j < IMG_WIDTH; j++) {
            vec3 color = camera.capture(scene, j, i, Camera::MSAA::X16);
            int red = (int)round(color.x * 255.0);
            int green = (int)round(color.y * 255.0);
            int blue = (int)round(color.z * 255.0);
            image.drawPixel(j, i,
                            (255 << 24) + red + (green << 8) + (blue << 16));
            printf("Pixel %d / %d\n", i * IMG_WIDTH + j,
                   IMG_WIDTH * IMG_HEIGHT);
        }

    // Print time taken.
    auto end_time = chrono::high_resolution_clock::now();
    auto sec = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    std::cout << sec.count() << " seconds taken.\n";

    // Make Window.
    Display display("A Window", SCREEN_WIDTH, SCREEN_HEIGHT);
    display.update(&image);

    // Window event loop.
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Poll events.
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }

    // Free resources and quit.
    SDL_Quit();
    return 0;
}