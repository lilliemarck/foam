#include <foam/pen.hh>

#include <foam/algorithm.hh>
#include <foam/editor.hh>

namespace foam {

pen::pen(editor& editor)
	: editor_(editor)
	, is_drawing_(false) {
}

void pen::on_mouse_axes(ALLEGRO_MOUSE_EVENT const& event) {
	auto world_position = editor_.get_camera().to_world_space({event.x, event.y});

	if (is_drawing_) {
		room& room = editor_.get_room();
		ALLEGRO_COLOR color = editor_.get_fg_color();
		bresenham_line(previous_position_, world_position, [&](int x, int y) {
			room.put_pixel(x, y, color);
		});
	}

	previous_position_ = world_position;
}

void pen::on_mouse_button_down(ALLEGRO_MOUSE_EVENT const& event) {
	previous_position_ = editor_.get_camera().to_world_space({event.x, event.y});

	if (event.button == 1) {
		room& room = editor_.get_room();
		ALLEGRO_COLOR color = editor_.get_fg_color();
		room.put_pixel(previous_position_.x(), previous_position_.y(), color);
		is_drawing_ = true;
	}
}

void pen::on_mouse_button_up(ALLEGRO_MOUSE_EVENT const& event) {
	if (event.button == 1) {
		is_drawing_ = false;
	}
}

} // namespace foam
