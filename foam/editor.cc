#include <foam/editor.hh>

#include <allegro5/allegro.h>
#include <foam/algorithm.hh>
#include <functional>

namespace foam {

editor::editor()
	: room_(std::make_shared<foam::room>(32, 20))
	, fg_color_(al_map_rgb(255, 127, 0))
	, mouse_x_(0)
	, mouse_y_(0)
	, mouse_down_(false) {
}

void editor::handle_event(ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
		if (mouse_down_) {
			using namespace std::placeholders;
			bresenham_line(mouse_x_, mouse_y_, event.mouse.x, event.mouse.y, std::bind(&room::put_pixel, room_, _1, _2, fg_color_));
			mouse_x_ = event.mouse.x;
			mouse_y_ = event.mouse.y;
		}
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		room_->put_pixel(event.mouse.x, event.mouse.y, fg_color_);
		mouse_x_ = event.mouse.x;
		mouse_y_ = event.mouse.y;
		mouse_down_ = true;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		mouse_down_ = false;
		break;
	}
}

void editor::draw() {
	room_->draw();
}

} // namespace foam
