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
