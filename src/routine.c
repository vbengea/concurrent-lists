#include "../incl/c_test.h"

static void insert_numbers(t_data *data) {
	int	i;
	int	number;
	int	failed;

	failed = 0;
	i = 0;
	while (i < data->n_random_numbers) {
		pthread_mutex_lock(&data->random);
		number = generate_random_number();
		pthread_mutex_unlock(&data->random);
		if (number >= 0) {
			pthread_mutex_lock(&data->insert_positive);
			if (!add_number_front(&data->positive, number))
				failed++;
			pthread_mutex_unlock(&data->insert_positive);
		}
		else {
			pthread_mutex_lock(&data->insert_negative);
			if (!add_number_front(&data->negative, number))
				failed++;
			pthread_mutex_unlock(&data->insert_negative);
		}
		i++;
	}
	if (failed > 0) {
		fprintf(stderr, "Thread %lu: Failed to allocate memory for %d numbers\n",
			pthread_self(), failed);
	}
}


void *routine(void *arg) {
	t_data	*data;

	data = (t_data *)arg;
	insert_numbers(data);

	return NULL;
}
