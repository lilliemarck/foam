#pragma once

#include <ui/window.hh>

namespace ui {

struct button : public window {
public:
	using handler = void();

	button();
	void set_handler(handler* handler);

private:
	void on_event(ALLEGRO_EVENT const& event) override;
	void on_draw() override;

	handler* handler_;
};

} // namespace ui
