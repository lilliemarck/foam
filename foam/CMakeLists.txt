add_executable(foam
	algorithm.hh
	editor.cc
	editor.hh
	main.cc
	room.cc
	room.hh
	sprite.cc
	sprite.hh)

target_link_libraries(foam
	ui
	allegro_primitives
	allegro
	allegro_main)
