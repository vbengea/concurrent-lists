#include "../incl/c_test.h"

int generate_random_number(struct drand48_data *buffer) {

	long int result;
	mrand48_r(buffer, &result);
	return (int)result;
}