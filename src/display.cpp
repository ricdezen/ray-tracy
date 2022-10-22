#include <cstdint>
#include <display.h>

Display::Display(const char *name, int width, int height)
    : m_width(width), m_height(height) {
    m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, width, height, 0);
}

Display::~Display() { SDL_DestroyWindow(m_window); }

void Display::show() { SDL_ShowWindow(m_window); }

void Display::hide() { SDL_HideWindow(m_window); }

/**
 * Lock the window's surface if needed.
 * Update a single pixel. No check for out of bounds is made.
 */
void Display::drawPixel(int x, int y, uint32_t color) {
    SDL_Surface *surface = SDL_GetWindowSurface(m_window);

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    // Point to the pixel's address and write the color.
    uint32_t *const pixel =
        (uint32_t *)((uint8_t *)surface->pixels + y * surface->pitch +
                     x * surface->format->BytesPerPixel);
    *pixel = color;

    SDL_UnlockSurface(surface);
}

void Display::update() { SDL_UpdateWindowSurface(m_window); }