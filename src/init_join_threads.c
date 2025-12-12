#include "../incl/c_test.h"

bool init_join_threads(t_data *data) {
	int	i;
	int	ret;

	i = 0;
	while (i < data->n_threads) {
		ret = pthread_create(&data->threads[i], NULL, routine, data);
		if (ret != 0) {
			// Join threads and return
			fprintf(stderr, "pthread_create failed: %s\n", strerror(ret));
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return false;
		}
		i++;
	}
	i = 0;
	while (i < data->n_threads) {
		ret = pthread_join(data->threads[i], NULL);
		if (ret != 0) {
			// Continue joining threads even if one fails
			fprintf(stderr, "pthread_join failed for thread %d: %s\n", i, strerror(ret));
		}
		i++;
	}

	return true;
}