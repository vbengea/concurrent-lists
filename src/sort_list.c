#include "../incl/c_test.h"

static int compare_ints(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

void sort_list(t_list *list) {
	int		size;
	int		*arr;
	t_list	*temp;

	size = list_size(list);
	if (!size)
		return;

	arr = malloc(sizeof(int) * size);
	temp = list;
	for (int i = 0; i < size; i++) {
		arr[i] = temp->number;
		temp = temp->next;
	}

	qsort(arr, size, sizeof(int), compare_ints);

	temp = list;
	for (int i = 0; i < size; i++) {
		temp->number = arr[i];
		temp = temp->next;
	}

	free(arr);
}