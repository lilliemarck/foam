#include <foam/room.hh>

#include <allegro5/allegro.h>
#include <foam/sprite.hh>

#define FOAM_TILE_SIZE 8

namespace foam {

room::room(unsigned width, unsigned height)
	: tiles_(width * height)
	, width_(width)
	, height_(height) {
	auto sprite = std::make_shared<foam::sprite>(FOAM_TILE_SIZE, FOAM_TILE_SIZE);
	for (auto& tile : tiles_) {
		tile = sprite;
	}
}

std::shared_ptr<sprite> room::get_tile(int x, int y) const {
	if (x >= 0 && x < int(width_) && y >= 0 && y < int(height_)) {
		return tiles_[width_ * y + x];
	}
	return {};
}

std::shared_ptr<sprite> room::get_tile_at_pixel(int x, int y) {
	return get_tile(x / FOAM_TILE_SIZE, y / FOAM_TILE_SIZE);
}

void room::put_pixel(int x, int y, ALLEGRO_COLOR color) {
	if (std::shared_ptr<sprite> tile = get_tile_at_pixel(x, y)) {
		tile->put_pixel(x % FOAM_TILE_SIZE, y % FOAM_TILE_SIZE, color);
	}
}

void room::draw() const {
	for (size_t y = 0; y < height_; ++y) {
		for (size_t x = 0; x < width_; ++x) {
			if (auto tile = get_tile(x, y)) {
				tile->draw(x * FOAM_TILE_SIZE, y * FOAM_TILE_SIZE);
			}
		}
	}
}

} // namespace foam
