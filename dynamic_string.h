#pragma once

#include <stdlib.h>

#define CHAR_PTR_TO_STRING_T(char_ptr__) \
	((((string_t *)(char_ptr__))) - 1)

typedef struct {
	size_t length;
	size_t capacity;
	char buf[];
} string_t;

char *new_string(const char *);

void free_string(char *);

void concat_target(char **target, const char *string);

