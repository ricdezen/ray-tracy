#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>

class Image {
public:
	Image(int width, int height);

	~Image();

	void drawPixel(int x, int y, uint32_t color);

	SDL_Surface* getSurface();

private:
	SDL_Surface* surface;
};

class Display {
public:
	/**
	 * Creates and shows a display (window).
	 */
	Display(const char* name, int width, int height);

	/**
	 * Called when the Display is destroyed.
	 */
	~Display();

	void show();               // Show window.
	void hide();               // Hide window.
	void update(Image* image); // Update window.

private:
	SDL_Window* m_window;
	int m_width;
	int m_height;
};

#endif // DISPLAY_H