#include "../incl/c_test.h"

bool add_number_front(t_list **list, int number) {
	t_list	*new_number;

	new_number = malloc(sizeof(t_list));
	if (!new_number){
		perror("malloc failed");
		return false;
	}

	new_number->number = number;
	new_number->next = *list;
	*list = new_number;

	return true;
}


bool add_number_back(t_list **list, int number) {
	t_list	*new_number;
	t_list	*temp;

	new_number = malloc(sizeof(t_list));
	if (!new_number){
		perror("malloc failed");
		return false;
	}

	new_number->number = number;
	new_number->next = NULL;

	if (!*list) {
		*list = new_number;
		return true;
	}
	temp = *list;

	while (temp->next)
		temp = temp->next;

	temp->next = new_number;

	return true;
}


void print_list(t_list *list) {
	t_list	*temp;
	static int i = 0;

	temp = list;
	while (temp) {
		printf("Number [%d]: %d\n", i, temp->number);
		temp = temp->next;
		i++;
	}
}

void free_list(t_list *list) {
	t_list	*temp;
	t_list	*next;

	temp = list;
	while (temp) {
		next = temp->next;
		free(temp);
		temp = next;
	}
}

int list_size(t_list *list) {
	int		i;
	t_list	*temp;

	if (!list)
		return 0;

	temp = list;
	i = 0;
	while (temp){
		temp = temp->next;
		i++;
	}
	return i;
}