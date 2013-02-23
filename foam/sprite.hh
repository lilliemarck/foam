#pragma once

#include <allegro5/allegro.h>

namespace foam {

class sprite {
public:
	sprite(unsigned width, unsigned height);
	~sprite();

	void put_pixel(int x, int y, ALLEGRO_COLOR color);
	void draw(int x, int y) const;

private:
	ALLEGRO_BITMAP *bitmap_;
};

} // namespace foam
