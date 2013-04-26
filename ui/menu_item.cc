#include <ui/menu_item.hh>

namespace ui {

menu_item::menu_item (const std::string& text)
	: text_(text) {
}

void menu_item::set_handler (handler handler) {
	handler_ = handler;
}

} // namespace ui
