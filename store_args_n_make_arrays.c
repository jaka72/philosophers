#include "philo.h"

int check_and_save_arguments(int argc, char *argv[], t_data *d)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error nr arguments\n");
		exit(0);
	}
	d->nrfilos = atoi(argv[1]);
	d->time_to_die = atoi(argv[2]);
	d->time_to_eat = atoi(argv[3]);
	d->time_to_sleep = atoi(argv[4]);
	d->nr_times_to_eat = -1;
	if (d->nrfilos < 0 || d->time_to_die < 0 ||
		d->time_to_eat < 0 || d->time_to_sleep < 0)
	{
		printf("Error: Invalid argument\n");
		exit(0);
	}
	if (argc == 6)
	{
		d->nr_times_to_eat = atoi(argv[5]);
		if (d->nr_times_to_eat == 0)
			exit(0);
		else if (d->nr_times_to_eat < 0)
		{
			printf("Error: Invalid argument\n");
			exit(0);
		}
	}
	return (0);
}


int	make_arrays_and_philos(t_data *d)
{
	int	i;

	d->fork_mutex = malloc(sizeof(pthread_mutex_t) * d->nrfilos);
	d->old_times_eaten = malloc(sizeof(int) * d->nrfilos);
	d->new_times_eaten = malloc(sizeof(int) * d->nrfilos);
	d->time_started_eating = malloc(sizeof(long int) * d->nrfilos);
	d->flag_has_started_eating = malloc(sizeof(int) * d->nrfilos);
	d->deadlines = malloc(sizeof(long int) * d->nrfilos);
		// check errors for all mallocs
	i = 0;
	while (i < d->nrfilos)
	{
		pthread_mutex_init(&d->fork_mutex[i], NULL);
		d->old_times_eaten[i] = 0;
		d->new_times_eaten[i] = 0;
		d->time_started_eating[i] = 0;
		d->deadlines[i] = d->time_to_die;
		i++;
	}
	return (0);
}