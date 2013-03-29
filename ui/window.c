#include <ui/window.h>

#include <allegro5/allegro.h>
#include <ui/array.h>
#include <stdbool.h>

struct ui_window {
	ui_window *parent;
	unsigned id;
	ui_rectangle frame;
	char *value;
	ui_window_proc proc;
	void *proc_data;
	struct ptr_array *children;
};

ui_window *ui_create_window(ui_window *parent, ui_window_proc proc, void *data) {
	ui_window *window = al_calloc(1, sizeof(struct ui_window));
	window->parent = parent;
	window->proc = proc;
	window->proc_data = data;
	window->children = ui_array_create();

	if (parent) {
		ui_array_push(parent->children, window);
	}

	if (proc) {
		proc(window, UI_MESSAGE_CREATE, 0);
	}

	return window;
}

void ui_destroy_window(ui_window *window) {
	if (!window) {
		return;
	}

	if (window->proc) {
		window->proc(window, UI_MESSAGE_DESTROY, 0);
	}

	for (size_t i = 0; i < ui_array_count(window->children); ++i) {
		ui_destroy_window(ui_array_get(window->children, i));
	}

	if (window->parent) {
		ui_array_remove(window->parent->children, window);
	}

	ui_array_release(window->children);
	al_free(window);
}

void *ui_get_proc_data(ui_window *window) {
	return window->proc_data;
}

ui_rectangle ui_get_frame(ui_window const *window) {
	return window->frame;
}

void ui_set_frame(ui_window *window, ui_rectangle frame) {
	window->frame = frame;
}

unsigned ui_get_id(ui_window const *window) {
	return window->id;
}

char const *ui_get_value(ui_window const* window) {
	return window->value;
}

void ui_set_value(ui_window *window, char const *value) {
	if (window->value != value) {
		size_t size = strlen(value) + 1;
		window->value = al_realloc(window->value, size);
		memcpy(window->value, value, size);
	}
}

void ui_draw(ui_window *window) {
	if (window->proc) {
		window->proc(window, UI_MESSAGE_DRAW, 0);
	}

	for (size_t i = 0; i < ui_array_count(window->children); ++i) {
		ui_draw(ui_array_get(window->children, i));
	}
}

static bool dispatch_mouse_event(ui_window *window, union ALLEGRO_EVENT const *event) {
	size_t i = ui_array_count(window->children);

	while (i-- > 0) {
		if (dispatch_mouse_event(ui_array_get(window->children, i), event)) {
			return true;
		}
	}

	int right = window->frame.x + window->frame.width;
	int bottom = window->frame.y + window->frame.height;
	if (event->mouse.x >= window->frame.x && event->mouse.x < right &&
	    event->mouse.y >= window->frame.y && event->mouse.y < bottom) {
		if (window->proc) {
			window->proc(window, UI_MESSAGE_EVENT, (intptr_t)event);
		}
		return true;
	}

	return false;
}

void ui_handle_event(ui_window *window, union ALLEGRO_EVENT const *event) {
	switch (event->type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		dispatch_mouse_event(window, event);
		break;
	}
}
