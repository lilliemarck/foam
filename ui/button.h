#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct ui_window;

typedef struct ui_window ui_button;
typedef void (*ui_button_handler)(ui_button *button, void *data);

ui_button *ui_button_create(struct ui_window *parent);
void ui_button_set_handler(ui_button *button, ui_button_handler handler, void *data);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
