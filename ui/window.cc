#include <ui/window.hh>

#include <allegro5/allegro.h>

namespace ui {

window::window(window_proc proc, void* data)
	: parent_(nullptr)
	, proc_(proc)
	, proc_data_(data) {
	if (proc) {
		proc(this, UI_MESSAGE_CREATE, 0);
	}
}

window::~window() {
	if (proc_) {
		proc_(this, UI_MESSAGE_DESTROY, 0);
	}

	detatch();
}

void window::append_child(window_ptr const& child)
{
	child->detatch();
	children_.push_back(child);
}

void window::detatch() {
	if (parent_) {
		auto& parent_children = parent_->children_;
		for (auto it = begin(parent_children); it != end(parent_children);) {
			if ((*it).get() == this) {
				it = parent_children.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

rectangle window::get_frame() const {
	return frame_;
}

void window::set_frame(rectangle const& frame) {
	frame_ = frame;
}

std::string const& window::get_value() const {
	return value_;
}

void window::set_value(char const* value) {
	value_ = value;
}

void window::draw() {
	if (proc_) {
		al_set_clipping_rectangle(frame_.x, frame_.y, frame_.width, frame_.height);
		proc_(this, UI_MESSAGE_DRAW, 0);
	}

	for (auto& child : children_) {
		child->draw();
	}
}

bool window::dispatch_mouse_event(ALLEGRO_EVENT const& event) {
	for (auto i = children_.rbegin(); i != children_.rend(); ++i) {
		if ((*i)->dispatch_mouse_event(event)) {
			return true;
		}
	}

	int right = frame_.x + frame_.width;
	int bottom = frame_.y + frame_.height;
	if (event.mouse.x >= frame_.x && event.mouse.x < right &&
	    event.mouse.y >= frame_.y && event.mouse.y < bottom) {
		if (proc_) {
			proc_(this, UI_MESSAGE_EVENT, reinterpret_cast<intptr_t>(&event));
		}
		return true;
	}

	return false;
}

void window::handle_event(ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		dispatch_mouse_event(event);
		break;
	}
}

} // namespace ui
