#pragma once

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <memory>
#include <vector>

union ALLEGRO_EVENT;

namespace ui {

#define UI_MESSAGE_CREATE   1
#define UI_MESSAGE_DESTROY  2
#define UI_MESSAGE_DRAW     3
#define UI_MESSAGE_EVENT    4

class window;
using window_ptr = std::shared_ptr<window>;
using window_proc = void(window* window, unsigned msg, intptr_t arg);

struct size {
	int width;
	int height;
};

struct rectangle {
	int x;
	int y;
	int width;
	int height;
};

inline bool is_inside(rectangle const& rectangle, int x, int y) {
	return x >= rectangle.x && x < rectangle.x + rectangle.width &&
	       y >= rectangle.y && y < rectangle.y + rectangle.height;
}

class window : private boost::noncopyable {
public:
	window();
	virtual ~window();

	void append_child(window_ptr const& child);
	void detatch();

	rectangle get_frame() const;
	void set_frame(rectangle const& frame);

	std::string const& get_value() const;
	void set_value(char const* value);

protected:
	virtual void on_draw() {}
	virtual void on_event(ALLEGRO_EVENT const& event) {}

private:
	void draw();

	window* parent_;
	rectangle frame_;
	std::string value_;
	std::vector<std::shared_ptr<window>> children_;

	friend class context;
};

} // namespace ui
