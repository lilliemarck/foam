add_library(ui
	button.cc
	button.hh
	control.hh
	menu.cc
	menu.hh
	menu_item.cc
	menu_item.hh
	window.cc
	window.hh)

target_link_libraries(ui
	allegro)
