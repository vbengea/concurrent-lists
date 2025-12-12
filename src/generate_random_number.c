#include "../incl/c_test.h"

int generate_random_number() {
	unsigned int r = (unsigned int)random() << 1 | (random() & 1);
	int number = (int)r;

	// printf("Test number: %d\n", test);
	return number;
}