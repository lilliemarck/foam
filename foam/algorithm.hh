#pragma once

#include <foam/vector.hh>
#include <cstdlib>

namespace foam {

template <typename PutPixel>
void bresenham_line(int x1, int y1, int x2, int y2, PutPixel put_pixel)
{
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;

	for (;;) {
		put_pixel(x1, y1);

		if (x1 == x2 && y1 == y2) {
			break;
		}

		int e2 = 2 * err;

		if (e2 > -dy) {
			err = err - dy;
			x1 = x1 + sx;
		}

		if (e2 < dx) {
			err = err + dx;
			y1 = y1 + sy;
		}
	}
}

template <typename PutPixel>
void bresenham_line(vector2i const& begin, vector2i const& end, PutPixel put_pixel) {
	bresenham_line(begin.x(), begin.y(), end.x(), end.y(), put_pixel);
}

} // namespace foam
