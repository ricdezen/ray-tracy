#include <SDL.h>
#include <camera.h>
#include <chrono>
#include <cstdio>
#include <display.h>
#include <hittable.h>
#include <iostream>
#include <thread>

namespace chrono = std::chrono;

// If expression does not eval to 0, print SDL error.
#define ERROR_WRAP_SDL(expression)                                             \
    {                                                                          \
        if (expression != 0)                                                   \
            printf(SDL_GetError());                                            \
    }

int main(int argc, char** args) {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int IMG_WIDTH = 1280;
	const int IMG_HEIGHT = 720;

	// Initialize SDL.
	ERROR_WRAP_SDL(SDL_Init(SDL_INIT_EVERYTHING));

	// Make scene.
	Scene scene({ Sphere(vec3(0, 0, -5), vec3(1, 1, 1), 1),
		Sphere(vec3(-2.005, 0, -5), vec3(1, 0, 0), 1),
		Sphere(vec3(2.005, 0, -5), vec3(0, 1, 0), 1),
		Sphere(vec3(0, -101.005, -5), vec3(0.8, 0.8, 0.8), 100) });

	// Make camera.
	Camera camera(IMG_WIDTH, IMG_HEIGHT);

	// Rendering parameters.
	RenderParams::SSAA msaa = RenderParams::SSAA::X16;
	int samples = 1024;
	int bounces = 16;
	int n_threads = std::thread::hardware_concurrency() - 1;
	printf("Generating image on %d threads.\n", n_threads);
	RenderParams params = { msaa, samples, bounces, n_threads };

	// Measure time.
	auto start_time = chrono::high_resolution_clock::now();

	// Generate image.
	Image* image = camera.capture(scene, params);

	// Print time taken.
	auto end_time = chrono::high_resolution_clock::now();
	auto sec = chrono::duration_cast<chrono::seconds>(end_time - start_time);
	std::cout << std::endl << sec.count() << " seconds taken.\n";

	// Make Window.
	Display display("A Window", SCREEN_WIDTH, SCREEN_HEIGHT);
	display.update(image);

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
	delete image;
	SDL_Quit();
	return 0;
}