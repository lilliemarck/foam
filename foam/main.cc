#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <foam/editor.hh>

int main() {
	if (!al_init())                  return 1;
	if (!al_install_mouse())         return 1;
	if (!al_init_primitives_addon()) return 1;

	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	ALLEGRO_DISPLAY *display = al_create_display(512, 320);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	foam::editor editor;
	bool run = true;
	ALLEGRO_EVENT event;

	while (run) {
		al_set_target_backbuffer(display);
		al_clear_to_color(black);
		editor.draw();
		al_flip_display();
		al_wait_for_event(event_queue, &event);

		do {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				run = false;
				break;
			}

			editor.handle_event(event);
		} while (al_get_next_event(event_queue, &event));
	}

	return 0;
}
