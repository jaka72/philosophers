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

int	store_arguments(int argc, char **argv, t_data *d)
{

	d->track_malloc[0] = 0;
	d->track_malloc[1] = 0;
	d->track_malloc[2] = 0;

	d->nrfilos = atoi(argv[1]);
	d->time_to_die = atoi(argv[2]);
	d->time_to_eat = atoi(argv[3]);
	d->time_to_sleep = atoi(argv[4]);
	d->max_meals_per_philo = -1;
	d->count_meals = 0;
	//d->mutex_forks = NULL;
	if (d->nrfilos <= 0 || d->time_to_die < 1 ||
		d->time_to_eat < 0 || d->time_to_sleep < 0)
	{
		printf("Error: Invalid argument value\n");
		return (1);
	}
	if (argc == 6)
	{
		d->max_meals_per_philo = atoi(argv[5]);
		if (d->max_meals_per_philo == 0)
			return (1);
		else if (d->max_meals_per_philo < 0)
		{
			printf("Error: Invalid argument\n");
			return (1);
		}
	}
//	return (d);
	return (0);
}

t_data	*check_and_store_arguments(int argc, char **argv)
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
	d->track_malloc[1] = 1;

	if (store_arguments(argc, argv, d) != 0)
	{
		free(d);// d MUST BE FREED, BECAUSE IT HAS BEEN ALREADY MALLOCED
		return (NULL);
	}
	return (d);
}
