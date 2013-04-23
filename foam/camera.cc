#include "camera.hh"

#include <algorithm>
#include <iostream>

namespace foam {

camera::camera()
	: position_{0, 0}
	, zoom_{1} {
}

vector2i camera::to_world_space(vector2i const& position) const {
    return position / zoom_ + position_;
}

vector2i camera::to_world_scale(vector2i const& size) const {
	return size / zoom_;
}

ALLEGRO_TRANSFORM camera::make_transform() const {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_translate_transform(&transform, -position_.x(), -position_.y());
	al_scale_transform(&transform, zoom_, zoom_);
	al_use_transform(&transform);
	return transform;
}

vector2i camera::get_position() const {
	return position_;
}

void camera::set_position(vector2i const& position) {
	position_ = position;
}

int camera::get_zoom() const {
	return zoom_;
}

void camera::set_zoom(int zoom, vector2i const& position) {
	if (zoom < 1) {
		zoom = 1;
	}

    position_ += position / zoom_ - position / zoom;
	zoom_ = zoom;
}

} // namespace foam
