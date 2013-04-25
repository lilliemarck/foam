#pragma once

#include <allegro5/allegro.h>
#include <foam/vector.hh>

namespace foam {

class editor;

class pen {
public:
	pen(editor& editor);

	void on_mouse_axes(ALLEGRO_MOUSE_EVENT const& event);
	void on_mouse_button_down(ALLEGRO_MOUSE_EVENT const& event);
	void on_mouse_button_up(ALLEGRO_MOUSE_EVENT const& event);

private:
	editor& editor_;
	vector2i previous_position_;
	bool is_drawing_;
};

} // namespace foam
