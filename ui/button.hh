#pragma once

#include <ui/button.h>
#include <ui/window.hh>

namespace ui {

class button : public window {
public:
	void create(window& parent) {
		set(ui_button_create(parent.get()));
	}

	void set_handler(ui_button_handler handler, void *data) {
		ui_button_set_handler(get(), handler, data);
	}
};

} // namespace ui
