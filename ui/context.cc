#include <ui/context.hh>

namespace ui {

window& context::root_window() {
	return root_window_;
}

void context::draw() {
	root_window_.draw();
}

void context::handle_event(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		root_window_.dispatch_mouse_event(event);
		break;
	}
}

} // namespace ui
