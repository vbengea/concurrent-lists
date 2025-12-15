#include "../incl/c_test.h"

int main(int argc, char **argv) {
	t_data	data;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <number of threads> <number of random numbers>\n", argv[0]);
		return 1;
	}
	if (!parse_args(argv + 1))
		return 2;

	if (!init_data(&data, argv)) {
		return 3;
	}
	else {
		init_join_threads(&data);
		sort_and_print(&data);
		cleanup(&data);
	}

	return 0;
}
