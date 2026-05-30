#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define STRING_MAGIC 0x53545247

#define CHAR_PTR_TO_STRING_T(ptr) \
	((string_t *)((char *)(ptr) - offsetof(string_t, buf)))

typedef struct {
	uint32_t magic;
	size_t length;
	size_t capacity;
	char buf[];
} string_t;

char *new_string(const char *);

void free_string(char *);

void concat_target(char **target, const char *string);

char *concat(const char *a, const char *b);
