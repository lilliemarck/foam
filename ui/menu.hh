#pragma once

#include <allegro5/allegro_font.h>
#include <boost/optional.hpp>
#include <ui/menu_item.hh>
#include <ui/window.hh>
#include <functional>
#include <vector>

namespace ui {

class menu : public window {
public:
	menu();
	void append_item(std::string const& text, menu_item::handler handler);

private:
	size wanted_size();
	void on_draw() override;
	void on_event(ALLEGRO_EVENT const& event) override;
	void update_highlight(int mouse_x, int mouse_y);

	std::shared_ptr<ALLEGRO_FONT> font_;
	std::vector<menu_item> items_;
	boost::optional<std::size_t> highlight_;
};

} // namespace ui
