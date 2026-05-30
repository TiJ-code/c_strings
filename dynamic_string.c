#include "dynamic_string.h"

#include <stdlib.h>
#include <string.h>

char *new_string(const char *string) {
	if (!string)
		return NULL;

	size_t header_length = sizeof(string_t);
	size_t string_length = strlen(string);	

	size_t total_length = header_length + string_length + 1;

	string_t *dyn_string = (string_t *)malloc(total_length);

	if (!dyn_string)
		return NULL;

	dyn_string->length   = string_length;
	dyn_string->capacity = string_length;

	strcpy(dyn_string->buf, string);

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

	size_t append_len = strlen(string);
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
			string,
			append_len + 1
	);

	target_string->length += append_len;
}


