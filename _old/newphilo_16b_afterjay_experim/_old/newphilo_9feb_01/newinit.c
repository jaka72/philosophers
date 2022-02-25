#include "newheader.h"

int		check_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("Error nr arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: arguments not only digits\n");
				return (1);	
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_data	*store_arguments(t_data *d, int argc, char **argv)
{
	d->nrfilos = atoi(argv[1]);
	d->time_to_die = atoi(argv[2]);
	//d->time_to_die += 4;
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

t_data	*check_and_save_arguments(int argc, char *argv[])
{
	t_data	*d;

	if (check_arguments(argc, argv) == 1)
		return (NULL);

	d = malloc(sizeof(t_data));
	if (d == NULL)
	{
		printf("Error mallocing data struct\n");
		return (NULL);
	}
	d = store_arguments(d, argc, argv);
	return (d);
}