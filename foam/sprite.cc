#include <foam/sprite.hh>

namespace foam {

sprite::sprite(unsigned width, unsigned height) {
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_RGBA_8888);
	bitmap_ = al_create_bitmap(8, 8);
}

sprite::~sprite() {
	al_destroy_bitmap(bitmap_);
}

void sprite::put_pixel(int x, int y, ALLEGRO_COLOR color) {
	al_set_target_bitmap(bitmap_);
	al_put_pixel(x, y, color);
}

void sprite::draw(int x, int y) const {
	al_draw_bitmap(bitmap_, x, y, 0);
}

} // namespace foam
