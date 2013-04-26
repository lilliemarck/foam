#pragma once

#include <ui/window.hh>
#include <functional>
#include <string>

namespace ui {

class menu_item {
public:
	using handler = std::function<void()>;

	menu_item(std::string const& text);
	void set_handler(handler handler);

private:
	std::string text_;
	handler handler_;

	friend class menu;
};

} // namespace ui
