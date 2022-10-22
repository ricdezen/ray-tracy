#include <SDL.h>
#include <camera.h>
#include <cstdio>
#include <display.h>
#include <hittable.h>

// If expression does not eval to 0, print SDL error.
#define ERROR_WRAP_SDL(expression)                                             \
    {                                                                          \
        if (expression != 0)                                                   \
            printf(SDL_GetError());                                            \
    }

int main(int argc, char **args) {
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 360;

    // Initialize SDL.
    ERROR_WRAP_SDL(SDL_Init(SDL_INIT_EVERYTHING));

    // Make Window.
    Display display("A Window", SCREEN_WIDTH, SCREEN_HEIGHT);
    Image image(IMG_WIDTH, IMG_HEIGHT);

    // Make scene.
    Scene scene({Sphere(vec3(0, 0, -5), 1)});

    // Make camera.
    Camera camera(IMG_WIDTH, IMG_HEIGHT);

    // Window event loop.
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Poll events.
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        // Draw on the surface.
        for (int i = 0; i < IMG_HEIGHT; i++)
            for (int j = 0; j < IMG_WIDTH; j++) {
                vec3 color = camera.capture(scene, j, i, Camera::MSAA::X16);
                int red = (int)round(color.x * 255.0);
                int green = (int)round(color.y * 255.0);
                int blue = (int)round(color.z * 255.0);
                image.drawPixel(
                    j, i, (255 << 24) + red + (green << 8) + (blue << 16));
            }

        display.update(&image);
    }

    // Free resources and quit.
    SDL_Quit();
    return 0;
}