#include <ui/button.hh>

#include <allegro5/allegro_primitives.h>
#include <ui/window.hh>

namespace ui {

typedef struct button_impl button_impl;

struct button_impl {
	button_impl() : handler(nullptr), handler_data(nullptr) {}

	button_handler* handler;
	void* handler_data;
};

static void draw_button(window* button) {
	rectangle rect = button->get_frame();
	ALLEGRO_COLOR color = al_map_rgb(0, 0, 255);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, color);
}

static void invoke_button_handler(window* button) {
	button_impl* impl = button->get_proc_data<button_impl>();
	if (impl && impl->handler) {
		impl->handler(button, impl->handler_data);
	}
}

static void handle_event(window* button, ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		invoke_button_handler(button);
	}
}

static void ui_button_proc(window* button, unsigned msg, intptr_t arg) {
	switch (msg) {
	case UI_MESSAGE_DESTROY:
		delete button->get_proc_data<button_impl>();
		break;
	case UI_MESSAGE_DRAW:
		draw_button(button);
		break;
	case UI_MESSAGE_EVENT:
		handle_event(button, *reinterpret_cast<ALLEGRO_EVENT*>(arg));
		break;
	}
}

window_ptr create_button() {
	return std::make_shared<window>(ui_button_proc, new button_impl);
}

void set_button_handler(window_ptr const& button, button_handler* handler, void* data) {
	button_impl* impl = button->get_proc_data<button_impl>();
	impl->handler = handler;
	impl->handler_data = data;
}

} // namespace ui
