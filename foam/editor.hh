#pragma once

#include <allegro5/allegro.h>
#include <foam/camera.hh>
#include <foam/pen.hh>
#include <foam/room.hh>
#include <foam/vector.hh>
#include <ui/button.hh>
#include <ui/window.hh>
#include <memory>

namespace foam {

using color_palette = std::vector<ALLEGRO_COLOR>;

class editor {
public:
	editor();

	void handle_event(ALLEGRO_EVENT const& event);
	void draw();

	camera& get_camera();
	room& get_room();
	color_palette& get_color_palette();
	ALLEGRO_COLOR get_fg_color() const;
	void set_fg_color(ALLEGRO_COLOR color);

private:
	void handle_mouse_axes(ALLEGRO_EVENT const& event);
	void handle_mouse_button_down(ALLEGRO_EVENT const& event);
	void handle_mouse_button_up(ALLEGRO_EVENT const& event);

	camera camera_;
	std::shared_ptr<room> room_;
	color_palette color_palette_;
	ALLEGRO_COLOR fg_color_;
	int mouse_z_;
	vector2i grab_position_;
	bool panning_;
	std::unique_ptr<pen> pen_;
	ui::window root_;
	ui::window color_dialog_;
	ui::button button_;
};

} // namespace foam
