#pragma once

#include <ui/window.hh>

namespace ui {

using button_handler = void(window* button, void* data);

window_ptr create_button();
void set_button_handler(window_ptr const& button, button_handler* handler, void* data);

} // namespace ui
