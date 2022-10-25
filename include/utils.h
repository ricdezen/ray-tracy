#ifndef UTILS_H
#define UTILS_H

#include <geom.h>

// --- Grid ---

/**
 * Just used to keep information about a rectangular grid for easier uniform
 * pixel sampling.
 */
class Grid {
  public:
    Grid() = default;

    /**
     * Define a 3D rectangle using 3 points.
     * @param o The top left point of the grid.
     * @param x The top right corner.
     * @param y The bottom left corner.
     * @param cells_x Number of grid cells along x.
     * @param cells_y Number of grid cells along y.
     */
    Grid(const vec3 &o, const vec3 &x, const vec3 &y, int cells_x, int cells_y);

    /**
     * Return top left corner of cell at the given coordinates.
     */
    vec3 cellTopLeft(int x, int y);

    /**
     * Return center of Grid element at the given coordinates.
     */
    vec3 cellCenter(int x, int y);

    // You guessed it.
    vec3 cellTopRight(int x, int y);
    vec3 cellBottomLeft(int x, int y);
    vec3 cellBottomRight(int x, int y);

    /**
     * Subgrid. Essentially split a cell into a smaller grid.
     */
    Grid subgrid(int x, int y, int cells_x, int cells_y);

  private:
    vec3 top_left;
    vec3 x_axis;
    vec3 y_axis;
    int cells_x;
    int cells_y;

    float width;
    float height;

    float cell_width;
    float cell_height;
    float cell_half_w;
    float cell_half_h;
};

// --- Progress bar ---

/**
 * @param progress from 0 to 1.
 * @param bar_size total size of the progress bar.
 */
void printProgress(float progress, int bar_size);

#endif