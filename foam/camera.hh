#pragma once

#include <allegro5/allegro.h>
#include <foam/vector.hh>

namespace foam {

class camera {
public:
	camera();

	vector2i to_world_space(vector2i const& position) const;
	vector2i to_world_scale(vector2i const& size) const;
	ALLEGRO_TRANSFORM make_transform() const;

	vector2i get_position() const;
	void set_position(vector2i const& position);

	int get_zoom() const;
	void set_zoom(int zoom, vector2i const& position);

private:
	vector2i position_;
	int zoom_;
};

} // namespace foam
