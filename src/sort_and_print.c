#include "../incl/c_test.h"

void sort_and_print(t_data *data) {
	sort_list(data->positive);
	sort_list(data->negative);

	print_list(data->negative);
	print_list(data->positive);
}