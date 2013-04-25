#include <foam/editor.hh>

#include <allegro5/allegro.h>
#include <foam/memory.hh>
#include <iostream>
#include <stdexcept>

namespace foam {

static void button_handler(ui_button *button, void *data) {
	std::cout << "button clicked" << std::endl;
}

editor::editor()
	: room_(std::make_shared<foam::room>(32, 20))
	, fg_color_(al_map_rgb(255, 127, 0))
	, mouse_z_{0}
	, panning_{false} {
	root_.create();
	root_.set_frame({0, 0, 512, 320});
	button_.create(root_);
	button_.set_frame({10, 10, 10, 16});
	button_.set_value("Button");
	button_.set_handler(button_handler, nullptr);
	pen_ = make_unique<pen>(*this);
}

void editor::handle_event(ALLEGRO_EVENT const& event) {
	root_.handle_event(event);

	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
		handle_mouse_axes(event);
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		handle_mouse_button_down(event);
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		handle_mouse_button_up(event);
		break;
	}
}

void editor::handle_mouse_axes(ALLEGRO_EVENT const& event) {
	vector2i mouse_position(event.mouse.x, event.mouse.y);
	auto world_position = camera_.to_world_space(mouse_position);

	if (panning_) {
		auto offset = camera_.to_world_scale(mouse_position);
		camera_.set_position(grab_position_ - offset);
	}

	int delta_z = event.mouse.z - mouse_z_;
	if (delta_z != 0) {
		camera_.set_zoom(camera_.get_zoom() + event.mouse.z - mouse_z_, world_position);
		mouse_z_ = event.mouse.z;
	}

	if (pen_) {
		pen_->on_mouse_axes(event.mouse);
	}
}

void editor::handle_mouse_button_down(ALLEGRO_EVENT const& event) {
	if (event.mouse.button == 2) {
		grab_position_ = camera_.to_world_space({event.mouse.x, event.mouse.y});
		panning_ = true;
	}

	if (pen_) {
		pen_->on_mouse_button_down(event.mouse);
	}
}

void editor::handle_mouse_button_up(ALLEGRO_EVENT const& event) {
	if (event.mouse.button == 2) {
		panning_ = false;
	}

	if (pen_) {
		pen_->on_mouse_button_up(event.mouse);
	}
}

void editor::draw() {
	ALLEGRO_TRANSFORM transform = camera_.make_transform();
	al_use_transform(&transform);
	room_->draw();

	al_identity_transform(&transform);
	al_use_transform(&transform);
	root_.draw();
}

camera& editor::get_camera() {
	return camera_;
}

room& editor::get_room() {
	if (!room_) {
		throw std::logic_error("Editor has no room to return.");
	}
	return *room_;
}

ALLEGRO_COLOR editor::get_fg_color() const {
	return fg_color_;
}

} // namespace foam
