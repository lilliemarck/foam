add_library(ui
	array.c
	array.h
	button.c
	button.h
	button.hh
	window.c
	window.h
	window.hh)

target_link_libraries(ui
	allegro)
