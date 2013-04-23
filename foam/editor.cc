#include <foam/editor.hh>

#include <allegro5/allegro.h>
#include <foam/algorithm.hh>
#include <iostream>
#include <functional>

namespace foam {

static void button_handler(ui_button *button, void *data) {
	std::cout << "button clicked" << std::endl;
}

editor::editor()
	: room_(std::make_shared<foam::room>(32, 20))
	, fg_color_(al_map_rgb(255, 127, 0))
	, world_mouse_{0, 0}
	, mouse_z_{0}
	, mouse_down_{false}
	, panning_{false} {
	root_.create();
	root_.set_frame({0, 0, 512, 320});
	button_.create(root_);
	button_.set_frame({10, 10, 10, 16});
	button_.set_value("Button");
	button_.set_handler(button_handler, nullptr);
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

	if (mouse_down_) {
		using namespace std::placeholders;
		bresenham_line(world_mouse_, world_position, std::bind(&room::put_pixel, room_, _1, _2, fg_color_));
	}

	if (panning_) {
		auto offset = camera_.to_world_scale(mouse_position);
		camera_.set_position(grab_position_ - offset);
	}

	int delta_z = event.mouse.z - mouse_z_;
	if (delta_z != 0) {
		camera_.set_zoom(camera_.get_zoom() + event.mouse.z - mouse_z_, world_position);
		mouse_z_ = event.mouse.z;
	}

	world_mouse_ = world_position;
}

void editor::handle_mouse_button_down(ALLEGRO_EVENT const& event) {
	world_mouse_ = camera_.to_world_space(vector2i(event.mouse.x, event.mouse.y));;

	if (event.mouse.button == 1) {
		room_->put_pixel(world_mouse_.x(), world_mouse_.y(), fg_color_);
		mouse_down_ = true;
	}
	else if (event.mouse.button == 2) {
		grab_position_ = world_mouse_;
		panning_ = true;
	}
}

void editor::handle_mouse_button_up(ALLEGRO_EVENT const& event) {
	if (event.mouse.button == 1) {
		mouse_down_ = false;
	}
	else if (event.mouse.button == 2) {
		panning_ = false;
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

} // namespace foam
