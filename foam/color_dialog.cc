#include <foam/color_dialog.hh>

#include <allegro5/allegro_primitives.h>
#include <boost/optional.hpp>
#include <foam/editor.hh>

namespace foam {
namespace {

int const well_size = 16;
int const spacing = 8;

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

} // namespace

color_dialog::color_dialog(editor& editor) : editor_(editor) {
}

bool color_dialog::on_event(ui::window& window, ALLEGRO_EVENT const& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			ui::rectangle rect = window.get_frame();
			int x = event.mouse.x - rect.x;
			int y = event.mouse.y - rect.y;

			if (auto color_index = position_to_color_index(x, y)) {
				auto const& palette = editor_.get_color_palette();

				if (*color_index < palette.size()) {
					editor_.set_fg_color(palette[*color_index]);
				}
			}
		}
	}

	return true;
}

void color_dialog::on_draw(ui::window& window) {
	ui::rectangle rect = window.get_frame();
	ALLEGRO_COLOR bg_color = al_map_rgb(63, 63, 63);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, bg_color);

	int x = rect.x + spacing;
	int y = rect.y + spacing;

	for (auto const& color : editor_.get_color_palette()) {
		al_draw_filled_rectangle(x, y, x + well_size, y + well_size, color);
		y += well_size + spacing;
	}
}

} // namespace foam
