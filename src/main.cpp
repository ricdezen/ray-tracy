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

    // Initialize SDL.
    ERROR_WRAP_SDL(SDL_Init(SDL_INIT_EVERYTHING));

    // Make Window.
    Display display("A Window", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Make scene.
    Scene scene({Sphere(vec3(0, 0, -5), 1)});

    // Make camera.
    Camera camera(1280, 720);

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
        for (int i = 0; i < SCREEN_HEIGHT; i++)
            for (int j = 0; j < SCREEN_WIDTH; j++) {
                vec3 color = camera.capture(scene, j, i);
                int red = (int)round(color.x * 255.0);
                int green = (int)round(color.y * 255.0);
                int blue = (int)round(color.z * 255.0);
                display.drawPixel(j, i, (red << 16) + (green << 8) + blue);
            }

        display.update();
    }

    // Free resources and quit.
    SDL_Quit();
    return 0;
}