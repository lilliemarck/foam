#pragma once

#include <allegro5/allegro.h>
#include <foam/room.hh>
#include <memory>

namespace foam {

class editor {
public:
	editor();

	void handle_event(ALLEGRO_EVENT const& event);
	void draw();

private:
	std::shared_ptr<room> room_;
	ALLEGRO_COLOR fg_color_;
};

} // namespace foam
