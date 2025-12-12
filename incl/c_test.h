#ifndef C_TEST_H
# define C_TEST_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_list {
	int				number;
	struct s_list	*next;
} t_list;

typedef struct s_data {
	int				n_threads;
	int				n_random_numbers;
	t_list			*positive;
	t_list			*negative;
	pthread_t		*threads;
	pthread_mutex_t	insert_positive;
	pthread_mutex_t	insert_negative;
	pthread_mutex_t	random;
} t_data;

int generate_random_number(void);

// List utils
bool add_number_front(t_list **list, int number);
bool add_number_back(t_list **list, int number);
void print_list(t_list *list);
void free_list(t_list *list);
int list_size(t_list *list);
void sort_list(t_list *list);

#endif