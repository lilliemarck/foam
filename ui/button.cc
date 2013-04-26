#include <ui/button.hh>

#include <allegro5/allegro_primitives.h>

namespace ui {

button::button()
	: handler_(nullptr) {
}

void button::set_handler(handler* handler) {
	handler_ = handler;
}

bool button::on_event(window& window, ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		if (handler_) {
			handler_();
			return true;
		}
	}

	return false;
}

void button::on_draw(window& window) {
	rectangle rect = window.get_frame();
	ALLEGRO_COLOR color = al_map_rgb(0, 0, 255);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, color);
}

} // namespace ui
