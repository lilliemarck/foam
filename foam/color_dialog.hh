#pragma once

#include <foam/editor.hh>
#include <ui/control.hh>

namespace foam {

class color_dialog : public ui::control {
public:
	color_dialog(editor& editor);

private:
	bool on_event(ui::window& window, ALLEGRO_EVENT const& event) override;
	void on_draw(ui::window& window) override;

	foam::editor& editor_;
};

} // namespace foam
