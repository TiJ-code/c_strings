#include "dynamic_string.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_dynamic_string(const char *str) {
	if (!str)
		return false;

	const string_t *s = CHAR_PTR_TO_STRING_T(str);

	return s->magic == STRING_MAGIC;
}

char *new_string(const char *string) {
	if (!string)
		return NULL;

	size_t header_length = sizeof(string_t);
	size_t string_length = strlen(string);	

	size_t total_length = header_length + string_length + 1;

	string_t *dyn_string = (string_t *)malloc(total_length);

	if (!dyn_string)
		return NULL;

	dyn_string->magic    = STRING_MAGIC; 
	dyn_string->length   = string_length;
	dyn_string->capacity = string_length;

	memcpy(dyn_string->buf, string, string_length + 1);

	return (char *)dyn_string->buf;
}

void free_string(char *dynamic_string) {
	if (!dynamic_string)
		return;

	string_t *dyn_string = ((string_t *)dynamic_string) - 1;

	free(dyn_string);
}

void concat_target(char **target, const char *string) {
	if (!target || !*target || !string)
		return;

	string_t *target_string = CHAR_PTR_TO_STRING_T(*target);

	size_t append_len;
	const char *src;

	if (is_dynamic_string(string)) {
		const string_t *s = CHAR_PTR_TO_STRING_T(string);
		append_len = s->length;
		src = s->buf;
	} else {
		append_len = strlen(string);
		src = string;
	}

	size_t required = target_string->length + append_len;

	if (required > target_string->capacity) {
		size_t new_capacity = target_string->capacity * 2;

		if (new_capacity < required)
			new_capacity = required;

		size_t new_size = sizeof(string_t) + new_capacity + 1;

		string_t *new_string = (string_t *)realloc(target_string, new_size);

		if (!new_string)
			return;

		new_string->capacity = new_capacity;
		target_string = new_string;

		*target = target_string->buf;
	}
	
	memcpy(
			target_string->buf + target_string->length,
			src,
			append_len
	);
	target_string->length += append_len;
	target_string->buf[target_string->length] = 0;
}

char *concat(const char *a, const char *b) {
	if (!a || !b)
		return NULL;

	size_t len_a;
	size_t len_b;

	if (is_dynamic_string(a))
		len_a = CHAR_PTR_TO_STRING_T(a)->length;
	else
		len_a = strlen(a);

	if (is_dynamic_string(b))
		len_b = CHAR_PTR_TO_STRING_T(b)->length;
	else
		len_b = strlen(b);

	size_t total = len_a + len_b;

	string_t *result = malloc(sizeof(string_t) + total + 1);

	if (!result)
		return NULL;

	result->magic = STRING_MAGIC;
	result->length = total;
	result->capacity = total;

	memcpy(result->buf, a, len_a);
	memcpy(result->buf + len_a, b, len_b);
	result->buf[total] = 0;

	return result->buf;
}

