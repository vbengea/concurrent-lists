#ifndef C_TEST_H
# define C_TEST_H

# define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ============================================================================
// Structures
// ============================================================================

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
} t_data;


// ============================================================================
// Random Number Generation
// ============================================================================

int generate_random_number(struct drand48_data *buffer);


// ============================================================================
// List Operations
// ============================================================================bool	add_number_front(t_list **list, int number);

bool	add_number_front(t_list **list, int number);
bool	add_number_back(t_list **list, int number);
void	print_list(t_list *list);
void	free_list(t_list *list);
int		list_size(t_list *list);
void	sort_list(t_list *list);


// ============================================================================
// Core Functions
// ============================================================================

void	cleanup(t_data *data);
void	*routine(void *arg);
bool	init_data(t_data *data, char **argv);
bool	init_join_threads(t_data *data);


// ============================================================================
// Parsing & Validation
// ============================================================================

bool	parse_args(char **argv);


// ============================================================================
// Output
// ============================================================================

void	sort_and_print(t_data *data);

#endif