#pragma once

#include <ui/window.h>

namespace ui {

class window {
public:
	window() : ptr_(nullptr) {
	}

	window(ui_window* ptr) : ptr_(ptr) {
	}

	~window() {
		ui_destroy_window(ptr_);
	}

	void create() {
		set(ui_create_window(nullptr, nullptr, nullptr));
	}

	void set_frame(ui_rectangle const& frame) {
		ui_set_frame(ptr_, frame);
	}

	void set_value(char const* value) {
		ui_set_value(ptr_, value);
	}

	void draw() {
		ui_draw(ptr_);
	}

	void handle_event(ALLEGRO_EVENT const& event) {
		ui_handle_event(ptr_, &event);
	}

	ui_window* get() {
		return ptr_;
	}

	void set(ui_window* ptr) {
		if (ptr_ != ptr) {
			ui_destroy_window(ptr_);
			ptr_ = ptr;
		}
	}

private:
	ui_window* ptr_;
};

} // namespace ui
