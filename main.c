#include "dynamic_string.h"

#include <stdio.h>

int main() {
	char *string = new_string("Hello");

	concat_target(&string, ", World");
	concat_target(&string, "!");

	char *new = concat(string, " What's up?");

	printf("%s\n", new);

	return 0;
}
