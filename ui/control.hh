#pragma once

#include <boost/noncopyable.hpp>

union ALLEGRO_EVENT;

namespace ui {

class window;

class control : private boost::noncopyable {
public:
	virtual ~control() {}
	virtual bool on_event(window& window, ALLEGRO_EVENT const& event) { return false; }
	virtual void on_draw(window& window) {}
};

} // namespace ui
