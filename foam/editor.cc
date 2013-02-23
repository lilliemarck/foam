#include <foam/editor.hh>

#include <allegro5/allegro.h>

namespace foam {

editor::editor()
	: room_(std::make_shared<foam::room>(32, 20))
	, fg_color_(al_map_rgb(255, 127, 0)) {
}

void editor::handle_event(ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		room_->put_pixel(event.mouse.x, event.mouse.y, fg_color_);
		break;
	}
}

void editor::draw() {
	room_->draw();
}

} // namespace foam
