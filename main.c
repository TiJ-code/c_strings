#include "dynamic_string.h"

#include <stdio.h>

int main() {
	char *string = new_string("Hello World!\n");

	printf("%s\n", string);

	return 0;
}
