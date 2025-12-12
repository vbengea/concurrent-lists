#include "../incl/c_test.h"

bool parse_args(char **argv) {
	int	i;
	int	j;

	i = 0;
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