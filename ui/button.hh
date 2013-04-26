#pragma once

#include <ui/window.hh>

namespace ui {

struct button : public control {
public:
	using handler = void();

	button();
	void set_handler(handler* handler);

private:
	bool on_event(window& window, ALLEGRO_EVENT const& event) override;
	void on_draw(window& window) override;

	handler* handler_;
};

} // namespace ui
