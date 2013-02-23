#include <allegro5/allegro.h>

int main() {
	if (!al_init()) {
		return 1;
	}

	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	ALLEGRO_DISPLAY *display = al_create_display(512, 320);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	ALLEGRO_EVENT event;

	for(;;) {
		al_clear_to_color(black);
		al_flip_display();
		al_wait_for_event(event_queue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return 0;
		}
	}

	return 0;
}
