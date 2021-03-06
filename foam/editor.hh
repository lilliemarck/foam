#pragma once

#include <allegro5/allegro.h>
#include <foam/camera.hh>
#include <foam/pen.hh>
#include <foam/room.hh>
#include <foam/vector.hh>
#include <ui/button.hh>
#include <ui/context.hh>
#include <ui/container.hh>
#include <ui/window.hh>
#include <memory>

namespace ui {
	class menu;
}

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
	ALLEGRO_COLOR get_color() const;
	std::size_t get_color_index() const;
	void set_color_index(std::size_t index);
	void show_menu(std::shared_ptr<ui::menu> const& menu);

private:
	void handle_mouse_axes(ALLEGRO_EVENT const& event);
	void handle_mouse_button_down(ALLEGRO_EVENT const& event);
	void handle_mouse_button_up(ALLEGRO_EVENT const& event);

	camera camera_;
	std::shared_ptr<room> room_;
	color_palette color_palette_;
	std::size_t color_index_;
	vector2i grab_position_;
	bool panning_;
	std::unique_ptr<pen> pen_;
	ui::context ui_context_;
	ui::container& root_container_;
	ui::window_ptr color_dialog_;
	std::shared_ptr<ui::button> button_;
};

} // namespace foam
