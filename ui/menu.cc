#include <ui/menu.hh>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <limits>

namespace ui {

menu::menu()
	: font_(al_load_font("lucon.ttf", 12, ALLEGRO_TTF_MONOCHROME), &al_destroy_font) {
}

void menu::append_item(std::string const& text, menu_item::handler handler) {
	menu_item item(text);
	item.set_handler(handler);
	items_.push_back(item);
}

size menu::wanted_size() {
	if (!items_.empty() && font_) {
		int widest = 0;

		for (auto const& item : items_) {
			int width = al_get_text_width(font_.get(), item.text_.c_str());
			if (width > widest) {
				widest = width;
			}
		}

		int total_height = items_.size() * al_get_font_line_height(font_.get());
		return {widest, total_height};
	} else {
		return {16, 16};
	}
}

void menu::on_event(ALLEGRO_EVENT const& event) {
	rectangle frame = get_frame();
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		if (highlight_) {
			update_highlight(event.mouse.x, event.mouse.y);
		}
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		update_highlight(event.mouse.x, event.mouse.y);
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if (is_inside(frame, event.mouse.x, event.mouse.y) && highlight_) {
			items_[*highlight_].handler_();
		}
		highlight_.reset();
	}
}

void menu::on_draw() {
	al_reset_clipping_rectangle();

	auto size = wanted_size();
	rectangle frame = get_frame();
	frame.width = size.width;
	frame.height = size.height;
	set_frame(frame);

	al_draw_filled_rectangle(frame.x, frame.y, frame.x + frame.width, frame.y + frame.height, al_map_rgb(63, 63, 63));

	if (font_) {
		int line_height = al_get_font_line_height(font_.get());
		int y = frame.y;
		for (std::size_t i = 0; i < items_.size(); ++i) {
			if (i == highlight_) {
				al_draw_filled_rectangle(frame.x, y, frame.x + frame.width, y + line_height, al_map_rgb(127, 127, 127));
			}

			al_draw_text(font_.get(), al_map_rgb(192, 192, 192), frame.x, y, 0, items_[i].text_.c_str());
			y += line_height;
		}
	}
}

void menu::update_highlight(int mouse_x, int mouse_y) {
	rectangle frame = get_frame();
	if (is_inside(frame, mouse_x, mouse_y) && font_) {
		mouse_y -= frame.y;
		highlight_ = mouse_y / al_get_font_line_height(font_.get());
	} else {
		highlight_.reset();
	}
}

} // namespace ui
