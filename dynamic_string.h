#pragma once

#include <stdlib.h>

typedef struct {
	size_t length;
	size_t capacity;
	char buf[];
} string_t;

char *new_string(const char *);

void free_string(char *);
