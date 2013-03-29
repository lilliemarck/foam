#include <ui/button.h>

#include <allegro5/allegro_primitives.h>
#include <ui/window.h>

typedef struct ui_button_impl ui_button_impl;

struct ui_button_impl {
	ui_button_handler handler;
	void *handler_data;
};

static void draw_button(ui_button *button) {
	ui_rectangle rect = ui_get_frame(button);
	ALLEGRO_COLOR color = al_map_rgb(0, 0, 255);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, color);
}

static void invoke_button_handler(ui_button *button) {
	ui_button_impl *impl = ui_get_proc_data(button);
	if (impl && impl->handler) {
		impl->handler(button, impl->handler_data);
	}
}

static void handle_event(ui_button *button, ALLEGRO_EVENT const *event) {
	switch (event->type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		invoke_button_handler(button);
	}
}

static void ui_button_proc(ui_button *button, unsigned msg, intptr_t arg) {
	switch (msg) {
	case UI_MESSAGE_DESTROY:
		al_free(ui_get_proc_data(button));
		break;
	case UI_MESSAGE_DRAW:
		draw_button(button);
		break;
	case UI_MESSAGE_EVENT:
		handle_event(button, (ALLEGRO_EVENT*)arg);
		break;
	}
}

ui_button *ui_button_create(ui_window *parent) {
	ui_button_impl *impl = al_calloc(1, sizeof(struct ui_button_impl));
	impl->handler = NULL;
	return ui_create_window(parent, ui_button_proc, impl);
}

void ui_button_set_handler(ui_button *button, ui_button_handler handler, void *data) {
	ui_button_impl *impl = ui_get_proc_data(button);
	impl->handler = handler;
	impl->handler_data = data;
}
