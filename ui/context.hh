#pragma once

#include <allegro5/allegro.h>
#include <boost/noncopyable.hpp>
#include <ui/window.hh>

namespace ui {

class context : private boost::noncopyable {
public:
	window& root_window();
	void draw();
	void handle_event(ALLEGRO_EVENT const& event);

private:
	void dispatch_mouse_event(ALLEGRO_EVENT const& event);

	window root_window_;
};

} // namespace ui
