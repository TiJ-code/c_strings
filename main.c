#include "dynamic_string.h"

#include <stdio.h>

int main() {
	char *string = new_string("Hello");

	concat_target(&string, ", World");
	concat_target(&string, "!");

	printf("%s\n", string);

	return 0;
}
