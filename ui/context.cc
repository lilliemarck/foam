#include <ui/context.hh>

namespace ui {

context::context()
	: container_(std::make_shared<ui::container>()) {
}

container& context::container() {
	return *container_;
}

void context::draw() {
	container_->draw();
}

void context::handle_event(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		collect_receivers(container_, event);
		dispatch_to_receivers(event);
		event_receivers_.clear();
		break;
	}
}

/*
 * It may not be necessary to send event to leaf windows first since events are
 * currently delivered to all windows even if the mouse is outside the windows
 * bounds.
 */
void context::collect_receivers(window_ptr const& window, ALLEGRO_EVENT const& event) {
	auto const& children = window->children_;
	for (auto i = children.rbegin(); i != children.rend(); ++i) {
		collect_receivers(*i, event);
	}

	event_receivers_.push_back(window);
}

void context::dispatch_to_receivers(ALLEGRO_EVENT const& event) {
	for (auto& window : event_receivers_) {
		window->on_event(event);
	}
}

} // namespace ui
