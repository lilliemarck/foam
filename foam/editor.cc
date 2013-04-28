#include <foam/editor.hh>

#include <allegro5/allegro.h>
#include <foam/memory.hh>
#include <foam/color_dialog.hh>
#include <ui/menu.hh>
#include <iostream>
#include <stdexcept>

namespace foam {

color_palette make_db_16_color_palette() {
	return {
		al_map_rgb( 20,  12,  28),
		al_map_rgb( 68,  36,  52),
		al_map_rgb( 48,  52, 109),
		al_map_rgb( 78,  74,  78),
		al_map_rgb(133,  76,  48),
		al_map_rgb( 52,  101, 36),
		al_map_rgb(208,  70,  72),
		al_map_rgb(117, 113,  97),
		al_map_rgb( 89, 125, 206),
		al_map_rgb(210, 125,  44),
		al_map_rgb(133, 149, 161),
		al_map_rgb(109, 170,  44),
		al_map_rgb(210, 170, 153),
		al_map_rgb(109, 194, 202),
		al_map_rgb(218, 212,  94),
		al_map_rgb(222, 238, 214)
	};
}

static void button_handler() {
	std::cout << "button clicked" << std::endl;
}

editor::editor()
	: room_(std::make_shared<foam::room>(32, 20))
	, color_palette_(make_db_16_color_palette())
	, color_index_(color_palette_.size() -1)
	, mouse_z_{0}
	, panning_(false)
	, root_window_(ui_context_.root_window()) {
	root_window_.set_frame({0, 0, 512, 320});

	color_dialog_ = std::make_shared<color_dialog>(*this);
	color_dialog_->set_frame({480, 0, 32, 320});
	root_window_.append_child(color_dialog_);

	button_ = std::make_shared<ui::button>();
	button_->set_frame({10, 10, 10, 16});
	button_->set_value("Button");
	button_->set_handler(&button_handler);
	root_window_.append_child(button_);

	pen_ = make_unique<pen>(*this);
}

void editor::handle_event(ALLEGRO_EVENT const& event) {
	ui_context_.handle_event(event);

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

	if (menu_) {
		// Modify root after all event dispatching has been finished
		root_window_.append_child(menu_);
		menu_.reset();
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
	ui_context_.draw();
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

color_palette& editor::get_color_palette() {
	return color_palette_;
}

ALLEGRO_COLOR editor::get_color() const {
	return color_palette_[color_index_];
}

std::size_t editor::get_color_index() const {
	return color_index_;
}

void editor::set_color_index(std::size_t index) {
	color_index_ = index;
}

void editor::show_menu(std::shared_ptr<ui::menu> const& menu) {
	menu_ = menu;
}

} // namespace foam
