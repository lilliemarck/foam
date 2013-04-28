#pragma once

#include <allegro5/allegro.h>
#include <boost/noncopyable.hpp>
#include <ui/window.hh>
#include <memory>

namespace ui {

class context : private boost::noncopyable {
public:
	context();
	window& root_window();
	void draw();
	void handle_event(ALLEGRO_EVENT const& event);

private:
	void collect_receivers(window_ptr const& window, ALLEGRO_EVENT const& event);
	void dispatch_to_receivers(ALLEGRO_EVENT const& event);

	window_ptr root_window_;
	std::vector<window_ptr> event_receivers_;
};

} // namespace ui
