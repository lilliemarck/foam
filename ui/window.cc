#include <ui/window.hh>

#include <allegro5/allegro.h>

namespace ui {

window::window()
	: parent_(nullptr) {
}

window::~window() {
	detatch();
}

void window::append_child(window_ptr const& child)
{
	child->detatch();
	children_.push_back(child);
	child->parent_ = this;
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
	al_set_clipping_rectangle(frame_.x, frame_.y, frame_.width, frame_.height);
	on_draw();

	for (auto& child : children_) {
		child->draw();
	}
}

void window::dispatch_mouse_event(ALLEGRO_EVENT const& event) {
	for (auto i = children_.rbegin(); i != children_.rend(); ++i) {
		(*i)->dispatch_mouse_event(event);
	}

	on_event(event);
}

} // namespace ui
