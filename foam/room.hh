#pragma once

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

namespace foam {

class sprite;

class room {
public:
	room(unsigned width, unsigned height);

	std::shared_ptr<sprite> get_tile(int x, int y) const;
	void put_pixel(int x, int y, ALLEGRO_COLOR color);
	void draw() const;

private:
	std::shared_ptr<sprite> get_tile_at_pixel(int x, int y);

	std::vector<std::shared_ptr<sprite>> tiles_;
	unsigned width_;
	unsigned height_;
};

} // namespace foam
