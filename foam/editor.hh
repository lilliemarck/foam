#pragma once

#include <allegro5/allegro.h>
#include <foam/camera.hh>
#include <foam/room.hh>
#include <foam/vector.hh>
#include <ui/button.hh>
#include <ui/window.hh>
#include <memory>

namespace foam {

class editor {
public:
	editor();

	void handle_event(ALLEGRO_EVENT const& event);
	void draw();

private:
	void handle_mouse_axes(ALLEGRO_EVENT const& event);
	void handle_mouse_button_down(ALLEGRO_EVENT const& event);
	void handle_mouse_button_up(ALLEGRO_EVENT const& event);

	camera camera_;
	std::shared_ptr<room> room_;
	ALLEGRO_COLOR fg_color_;
	vector2i world_mouse_;
	int mouse_z_;
	bool mouse_down_;
	vector2i grab_position_;
	bool panning_;
	ui::window root_;
	ui::button button_;
};

} // namespace foam
