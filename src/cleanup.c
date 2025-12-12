#include "../incl/c_test.h"

void cleanup(t_data *data) {

	free(data->threads);
	free_list(data->positive);
	free_list(data->negative);

	pthread_mutex_destroy(&data->insert_negative);
	pthread_mutex_destroy(&data->insert_positive);
	pthread_mutex_destroy(&data->random);
}