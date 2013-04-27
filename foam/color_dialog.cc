#include <foam/color_dialog.hh>

#include <allegro5/allegro_primitives.h>
#include <boost/algorithm/clamp.hpp>
#include <boost/optional.hpp>
#include <foam/editor.hh>
#include <ui/menu.hh>

namespace foam {
namespace {

int const border = 6;
int const well_size = 16;
int const spacing = 4;

boost::optional<unsigned> position_to_color_index(int x, int y) {
	x -= border;
	y -= border;

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

color_dialog::color_dialog(editor& editor)
	: editor_(editor)
	, first_index_(0) {
}

void color_dialog::on_event(ALLEGRO_EVENT const& event) {
	ui::rectangle const rect = get_frame();
	auto const& palette = editor_.get_color_palette();

	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
		if (is_inside(rect, event.mouse.x, event.mouse.y)) {
			int content_height = rect.height - 2 * border + spacing;
			std::size_t visible_wells = std::max(content_height / (well_size + spacing), 0);

			if (visible_wells < palette.size()) {
				int max_index = palette.size() - visible_wells;
				int new_index = first_index_ - event.mouse.dz;
				first_index_ = boost::algorithm::clamp(new_index, 0, max_index);
			}
			else {
				first_index_ = 0;
			}
		}
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		if (is_inside(rect, event.mouse.x, event.mouse.y)) {
			int x = event.mouse.x - rect.x;
			int y = event.mouse.y - rect.y;

			if (auto optional_index = position_to_color_index(x, y)) {
				std::size_t index = *optional_index + first_index_;
				if (index < palette.size()) {
					editor_.set_color_index(index);

					if (event.mouse.button == 2) {
						show_context_menu(event.mouse.x, event.mouse.y);
					}
				}
			}
		}
		break;
	}
}

void color_dialog::on_draw() {
	ui::rectangle rect = get_frame();
	ALLEGRO_COLOR bg_color = al_map_rgb(63, 63, 63);
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, bg_color);

	int x = rect.x + border;
	int y = rect.y + border;
	int bottom = rect.y + rect.height;

	auto const& palette = editor_.get_color_palette();
	std::size_t selected = editor_.get_color_index();

	for (std::size_t i = first_index_; i < palette.size(); ++i) {
		if (i == selected) {
			al_draw_filled_rectangle(x - 2, y - 2, x + well_size + 2, y + well_size + 2, al_map_rgb(0, 0, 0));
		}

		al_draw_filled_rectangle(x, y, x + well_size, y + well_size, palette[i]);
		y += well_size + spacing;

		if (y > bottom) {
			break;
		}
	}
}

void color_dialog::show_context_menu(int x, int y) {
	auto& palette = editor_.get_color_palette();

	auto menu = std::make_shared<ui::menu>();
	menu->append_item("Add Color", [&](){
		std::size_t index = palette.size();
		palette.push_back(al_map_rgb(255, 255, 255));
		editor_.set_color_index(index);
	});
	menu->append_item("Edit Color", [&](){

	});
	menu->append_item("Remove Color", [&](){
		if (palette.size() > 1) {
			std::size_t index = editor_.get_color_index();
			palette.erase(begin(palette) + index);

			if (index >= palette.size()) {
				editor_.set_color_index(palette.size() - 1);
			}
		}
	});

	menu->set_frame({x, y, 0, 0});
	editor_.show_menu(menu);
}

} // namespace foam
