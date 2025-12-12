#include "../incl/c_test.h"

bool add_number_front(t_list **list, int number) {
	t_list *new_number = malloc(sizeof(t_list));
	if (!new_number){
		return false;
	}

	new_number->number = number;
	new_number->next = *list;
	*list = new_number;

	return true;
}


bool add_number_back(t_list **list, int number) {
	t_list *new_number = malloc(sizeof(t_list));
	if (!new_number){
		return false;
	}

	new_number->number = number;
	new_number->next = NULL;

	if (!*list) {
		*list = new_number;
		return true;
	}
	t_list *temp = *list;

	while (temp->next)
		temp = temp->next;

	temp->next = new_number;

	return true;
}


void print_list(t_list *list) {
	t_list *temp;

	temp = list;
	while (temp) {
		printf("Number: %d\n", temp->number);
		temp = temp->next;
	}
}

void free_list(t_list *list) {
	t_list *temp;
	t_list *next;

	temp = list;
	while (temp) {
		next = temp->next;
		free(temp);
		temp = next;
	}
}