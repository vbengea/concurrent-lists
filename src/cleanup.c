#include "../incl/c_test.h"

void cleanup(t_data *data) {

	if (data->threads)
		free(data->threads);
	if (data->positive)
		free_list(data->positive);
	if (data->negative)
		free_list(data->negative);

	pthread_mutex_destroy(&data->insert_negative);
	pthread_mutex_destroy(&data->insert_positive);
	pthread_mutex_destroy(&data->random);
}