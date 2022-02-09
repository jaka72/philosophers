#include "newheader.h"

t_data	*check_and_save_arguments(int argc, char *argv[])
{
	int		i;
	int		j;
	t_data	*d;

	if (argc != 5 && argc != 6)
	{
		printf("Error nr arguments\n");
		return (NULL);
	}
	
	// TO ADD: CHECK IF ALL ARGUMENTS ARE ONLY DIGITS!
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: arguments not only digits\n");
				return (NULL);	
			}
			j++;
		}
		i++;
	}



	d = malloc(sizeof(t_data));
	if (d == NULL)
	{
		printf("Error mallocing data struct\n");
		return (NULL);
	}


	d->nrfilos = atoi(argv[1]);
	d->time_to_die = atoi(argv[2]);
	d->time_to_eat = atoi(argv[3]);
	d->time_to_sleep = atoi(argv[4]);
	d->nr_times_to_eat = -1;
	if (d->nrfilos <= 0 || d->time_to_die < 1 ||		// ASK IF OK nrphilos < 1
		d->time_to_eat < 0 || d->time_to_sleep < 0)	// or time to to die ... < 60 ...
	{
		printf("Error: Invalid argument value\n");
		return (NULL);
	}
	if (argc == 6)
	{
		d->nr_times_to_eat = atoi(argv[5]);
		if (d->nr_times_to_eat == 0)
			return (NULL);
		else if (d->nr_times_to_eat < 0)
		{
			printf("Error: Invalid argument\n");
			return (NULL);
		}
	}
	return (d);
}
