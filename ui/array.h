#pragma once

#include <stddef.h>

typedef struct ptr_array ptr_array;

ptr_array *ui_array_create(void);
void ui_array_release(ptr_array *array);
void ui_array_push(ptr_array *array, void *element);
void *ui_array_pop(ptr_array *array);
void *ui_array_back(ptr_array *array);
void *ui_array_get(ptr_array *array, size_t index);
void ui_array_put(ptr_array *array, size_t index, void *element);
void ui_array_erase(ptr_array *array, size_t index);
void ui_array_remove(ptr_array *array, void const *element);
void ui_array_clear(ptr_array *array);
size_t ui_array_count(ptr_array const *array);
