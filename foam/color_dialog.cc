#include <foam/color_dialog.hh>

#include <allegro5/allegro_primitives.h>
#include <boost/optional.hpp>
#include <foam/editor.hh>
#include <cstdlib>
#include <iostream>

namespace foam {
namespace {

int const well_size = 16;
int const spacing = 8;

struct color_dialog_impl {
	foam::editor& editor;
};

void draw_color_dialog(ui::window* window) {
	color_dialog_impl const& impl = *window->get_proc_data<color_dialog_impl>();

	ui::rectangle rect = window->get_frame();
	ALLEGRO_COLOR bg_color = al_map_rgb(63, 63, 63);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, bg_color);

	int x = rect.x + spacing;
	int y = rect.y + spacing;

	for (auto const& color : impl.editor.get_color_palette()) {
		al_draw_filled_rectangle(x, y, x + well_size, y + well_size, color);
		y += well_size + spacing;
	}
}

boost::optional<unsigned> position_to_color_index(int x, int y) {
	x -= spacing;
	y -= spacing;

	if (x < 0 || x >= well_size) {
		return {};
	}

	int stride = well_size + spacing;
	int y_mod = y % stride;

	if (y_mod < 0 || y_mod >= well_size) {
		return {};
	}

	return y / stride;
}

void handle_event(ui::window* window, ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			color_dialog_impl const& impl = *window->get_proc_data<color_dialog_impl>();
			ui::rectangle rect = window->get_frame();
			int x = event.mouse.x - rect.x;
			int y = event.mouse.y - rect.y;

			if (auto color_index = position_to_color_index(x, y)) {
				auto const& palette = impl.editor.get_color_palette();

				if (*color_index < palette.size()) {
					impl.editor.set_fg_color(palette[*color_index]);
				}
			}
		}
	}
}

void color_dialog_proc(ui::window* window, unsigned msg, intptr_t arg) {
	switch (msg) {
	case UI_MESSAGE_DESTROY:
		delete window->get_proc_data<color_dialog_impl>();
		break;
	case UI_MESSAGE_DRAW:
		draw_color_dialog(window);
		break;
	case UI_MESSAGE_EVENT:
		handle_event(window, *reinterpret_cast<ALLEGRO_EVENT*>(arg));
		break;
	}
}

} // namespace

ui::window_ptr create_color_dialog(editor& editor) {
	return std::make_shared<ui::window>(&color_dialog_proc, new color_dialog_impl{editor});
}

} // namespace foam
