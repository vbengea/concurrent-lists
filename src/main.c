#include "../incl/c_test.h"

// Check each character of the string to see if it's a number
bool parse_args(char **argv) {
	int	i = 0;
	int j = 0;

	while (argv[i]) {
		j = 0;
		while (argv[i][j]) {
			if (argv[i][j] > '9' || argv[i][j] < '0') {
				fprintf(stderr, "Args must be numbers\n");
				return false;
			}
			j++;
		}
		i++;
	}
	return true;
}


bool init_data(t_data *data, char **argv) {
	data->positive = NULL;
	data->negative = NULL;

	// Limit later the number of threads and numbers.
	// Also check for negative or 0 input
	data->n_threads = atoi(argv[1]);
	data->n_random_numbers = atoi(argv[2]);

	// Temporary malloc
	data->threads = malloc(sizeof(pthread_t) * data->n_threads);

	pthread_mutex_init(&data->insert_positive, NULL);
	pthread_mutex_init(&data->insert_negative, NULL);
	pthread_mutex_init(&data->random, NULL);

	return true;
}

void insert_numbers(t_data *data) {
	int i = 0;
	int number;
	while (i < data->n_random_numbers) {
		pthread_mutex_lock(&data->random);
		number = generate_random_number();
		pthread_mutex_unlock(&data->random);
		if (number >= 0) {
			pthread_mutex_lock(&data->insert_positive);
			add_number_front(&data->positive, number);
			pthread_mutex_unlock(&data->insert_positive);
		}
		else {
			pthread_mutex_lock(&data->insert_negative);
			add_number_front(&data->negative, number);
			pthread_mutex_unlock(&data->insert_negative);
		}
		i++;
	}
}


void *routine(void *arg) {
	// printf("Working!\n");
	t_data *data = (t_data *)arg;

	insert_numbers(data);

	return NULL;
}


// Fisrst arg: Total number of threads
// Second arg: Total numbers that each thread generates
int main(int argc, char **argv) {
	t_data	data;
	srandom(time(NULL));

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <number of threads> <number of random numbers>\n", argv[0]);
		return 1;
	}

	if (!parse_args(argv + 1)) // Skip the name of the program
		return 2;

	if (!init_data(&data, argv)) {
		// Error handling ?
		return 3;
	}
	else {
		// Initialize threads
		int i = 0;
		while (i < data.n_threads) {
			pthread_create(&data.threads[i], NULL, routine, &data);
			i++;
		}
		i = 0;
		while (i < data.n_threads) {
			pthread_join(data.threads[i], NULL);
			i++;
		}

		print_list(data.positive);
		print_list(data.negative);

		// Sort
		// Print
		// Free and Clean
	}

	return 0;
}
