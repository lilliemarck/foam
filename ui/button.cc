#include <ui/button.hh>

#include <allegro5/allegro_primitives.h>

namespace ui {

button::button()
	: handler_(nullptr) {
}

void button::set_handler(handler* handler) {
	handler_ = handler;
}

void button::on_event(ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		if (is_inside(get_frame(), event.mouse.x, event.mouse.y) && handler_) {
			handler_();
		}
	}
}

void button::on_draw() {
	rectangle rect = get_frame();
	ALLEGRO_COLOR color = al_map_rgb(0, 0, 255);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, color);
}

} // namespace ui
