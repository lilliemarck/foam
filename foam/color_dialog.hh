#pragma once

#include <foam/editor.hh>
#include <ui/window.hh>

namespace foam {

class color_dialog : public ui::window {
public:
	color_dialog(editor& editor);

private:
	void on_event(ALLEGRO_EVENT const& event) override;
	void on_draw() override;

	foam::editor& editor_;
	int first_index_;
};

} // namespace foam
