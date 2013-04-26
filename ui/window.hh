#pragma once

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

struct rectangle {
	int x;
	int y;
	int width;
	int height;
};

class window {
public:
	window(window_proc* proc = nullptr, void* data = nullptr);
	~window();

	void append_child(window_ptr const& child);
	void detatch();

	template <typename T>
	T* get_proc_data() {
		return static_cast<T*>(proc_data_);
	}

	rectangle get_frame() const;
	void set_frame(rectangle const& frame);

	std::string const& get_value() const;
	void set_value(char const* value);

	void draw();
	void handle_event(ALLEGRO_EVENT const& event);

private:
	bool dispatch_mouse_event(ALLEGRO_EVENT const& event);

	window* parent_;
	rectangle frame_;
	std::string value_;
	window_proc* proc_;
	void* proc_data_;
	std::vector<std::shared_ptr<window>> children_;
};

} // namespace ui
