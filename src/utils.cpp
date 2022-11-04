#include <utils.h>

// --- Grid ---

Grid::Grid(
	const vec3& o, const vec3& x, const vec3& y, int cells_x, int cells_y
) : top_left(o), cells_x(cells_x), cells_y(cells_y) {
	vec3 xo = x - o;
	vec3 yo = y - o;

	x_axis = normalize(xo);
	y_axis = normalize(yo);

	width = length(xo);
	height = length(yo);

	cell_width = width / cells_x;
	cell_height = height / cells_y;
	cell_half_w = cell_width / 2;
	cell_half_h = cell_height / 2;
}

vec3 Grid::cellTopLeft(int x, int y) {
	return top_left + x_axis * cell_width * (float)x +
		y_axis * cell_height * (float)y;
}

vec3 Grid::cellCenter(int x, int y) {
	return cellTopLeft(x, y) + x_axis * cell_half_w + y_axis * cell_half_h;
}

vec3 Grid::cellTopRight(int x, int y) {
	return cellTopLeft(x + 1, y);
}
vec3 Grid::cellBottomLeft(int x, int y) {
	return cellTopLeft(x, y + 1);
}
vec3 Grid::cellBottomRight(int x, int y) {
	return cellTopLeft(x + 1, y + 1);
}

Grid Grid::subgrid(int x, int y, int cells_x, int cells_y) {
	return Grid(
		cellTopLeft(x, y), cellTopRight(x, y), cellBottomLeft(x, y), cells_x, cells_y
	);
}

// --- Progress bar ---

void printProgress(float progress, int bar_size) {
	// Need terminating 0 and initial \r
	char* str = (char*)calloc(bar_size - 2, sizeof(char));

	// TODO: move elsewhere or standardize.
	if (str == nullptr) {
		printf("null pointer in malloc");
		exit(1);
	}

	memset(str, ' ', bar_size - 2);

	// 0 terminator.
	str[bar_size - 3] = 0;
	// Carriage return.
	str[0] = '\r';

	// Fill the progress.
	memset(str + 2, '#', (int)round(progress * (bar_size - 6)));

	// First and last brackets.
	str[1] = '[';
	str[bar_size - 4] = ']';

	// Print bar and progress.
	printf("%s%3d%%", str, (int)round(progress * 100));
	free(str);
}