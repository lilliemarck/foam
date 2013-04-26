#pragma once

#include <foam/editor.hh>
#include <ui/window.hh>

namespace foam {

ui_window* create_color_dialog(ui_window* parent, editor& editor);

} // namespace foam
