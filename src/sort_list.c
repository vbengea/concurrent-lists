#include "../incl/c_test.h"

void sort_list(t_list *list) {
	int		size;
	int		i;
	int		j;
	t_list	*temp;
	
	size = list_size(list);

	i = 0;
	while (i < size) {
		j = 0;
		temp = list;
		while (j < size - i - 1 && temp->next) {
			if (temp->number > temp->next->number) {
				int temp_n = temp->next->number;
				temp->next->number = temp->number;
				temp->number = temp_n;
			}
			temp = temp->next;
			j++;
		}
		i++;
	}
}
