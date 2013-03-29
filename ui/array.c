#include <ui/array.h>

#include <allegro5/allegro.h>

struct ptr_array {
	void **begin;
	void **end;
	void **capacity;
};

ptr_array *ui_array_create(void) {
	ptr_array *array = al_malloc(sizeof(*array));
	array->begin = NULL;
	array->end = NULL;
	array->capacity = NULL;
	return array;
}

void ui_array_release(ptr_array *array) {
	if (array) {
		al_free(array->begin);
		al_free(array);
	}
}

void ui_array_push(ptr_array *array, void *object) {
	if (array->end == array->capacity) {
		size_t length   = array->end - array->begin;
		size_t capacity = (length + 1) << 1;
		array->begin    = al_realloc(array->begin, capacity * sizeof(void*));
		array->end      = array->begin + length;
		array->capacity = array->begin + capacity;
	}
	*array->end++ = object;
}

void *ui_array_pop(ptr_array *array) {
	return *--array->end;
}

void *ui_array_back(ptr_array *array) {
	return *(array->end - 1);
}

void *ui_array_get(ptr_array *array, size_t index) {
	return array->begin[index];
}

void ui_array_put(ptr_array *array, size_t index, void *element) {
	array->begin[index] = element;
}

void ui_array_erase(ptr_array *array, size_t index) {
	memcpy(array->begin + index,
	       array->begin + index + 1,
	       sizeof(void*) * (--array->end - array->begin - index));
}

void ui_array_remove(ptr_array *array, void const *element) {
	size_t count = ui_array_count(array);
	size_t i = 0;
	while (i < count) {
		if (array->begin[i] == element) {
			ui_array_erase(array, i);
			--count;
		} else {
			++i;
		}
	}
}

void ui_array_clear(ptr_array *array) {
	array->end = array->begin;
}

size_t ui_array_count(ptr_array const *array) {
	return array->end - array->begin;
}
