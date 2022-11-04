#include <cstdint>
#include <display.h>

// --- Image ---

Image::Image(int width, int height) {
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    surface =
        SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
}

Image::~Image() { SDL_FreeSurface(surface); }

/**
 * Lock the surface if needed.
 * Update a single pixel. No check for out of bounds is made.
 */
void Image::drawPixel(int x, int y, uint32_t color) {
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    // Point to the pixel's address and write the color.
    uint32_t* const pixel = (uint32_t*)((uint8_t*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

    *pixel = color;

    SDL_UnlockSurface(surface);
}

SDL_Surface *Image::getSurface() { return surface; }

// --- Display ---

Display::Display(const char *name, int width, int height)
    : m_width(width), m_height(height) {
    m_window = SDL_CreateWindow(
        name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0
    );
}

Display::~Display() { SDL_DestroyWindow(m_window); }

void Display::show() { SDL_ShowWindow(m_window); }

void Display::hide() { SDL_HideWindow(m_window); }

void Display::update(Image *image) {
    SDL_BlitScaled(
        image->getSurface(), NULL, SDL_GetWindowSurface(m_window), NULL
    );
    SDL_UpdateWindowSurface(m_window);
}