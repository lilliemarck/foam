#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

#define UI_MESSAGE_CREATE   1
#define UI_MESSAGE_DESTROY  2
#define UI_MESSAGE_DRAW     3
#define UI_MESSAGE_EVENT    4

struct ptr_array;
union ALLEGRO_EVENT;

typedef struct ui_rectangle ui_rectangle;
typedef struct ui_window ui_window;
typedef void (*ui_window_proc)(ui_window *window, unsigned msg, intptr_t arg);

struct ui_rectangle {
	int x;
	int y;
	int width;
	int height;
};

ui_window *ui_create_window(ui_window *parent, ui_window_proc proc, void *data);
void ui_destroy_window(ui_window *window);
void *ui_get_proc_data(ui_window *window);
ui_rectangle ui_get_frame(ui_window const *window);
void ui_set_frame(ui_window *window, ui_rectangle frame);
unsigned ui_get_id(ui_window const *window);
char const *ui_get_value(ui_window const* window);
void ui_set_value(ui_window *window, char const *value);
void ui_draw(ui_window *window);
void ui_handle_event(ui_window *window, union ALLEGRO_EVENT const *event);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
