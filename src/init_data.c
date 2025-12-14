#include "../incl/c_test.h"

static bool init_mutex(t_data *data) {
	int	ret;

	ret = pthread_mutex_init(&data->insert_positive, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_mutex_init failed: %s\n", strerror(ret));
		free(data->threads);
		return false;
	}
	
	ret = pthread_mutex_init(&data->insert_negative, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_mutex_init failed: %s\n", strerror(ret));
		free(data->threads);
		pthread_mutex_destroy(&data->insert_positive);
		return false;
	}

	return true;
}

bool init_data(t_data *data, char **argv) {
	data->positive = NULL;
	data->negative = NULL;
	data->n_threads = atoi(argv[1]);
	if (data->n_threads <= 0 || data->n_threads >= 1000) {
		fprintf(stderr, "Number of threads must be between 1 and 1000\n");
		return false;
	}
	data->n_random_numbers = atoi(argv[2]);
	if (data->n_random_numbers <= 0 || data->n_random_numbers >= 100000) {
		fprintf(stderr, "Number of random numbers must be between 1 and 100000\n");
		return false;
	}
	data->threads = malloc(sizeof(pthread_t) * data->n_threads);
	if (!data->threads) {
		perror("malloc failed");
		return false;
	}
	if (!init_mutex(data))
		return false;

	return true;
}