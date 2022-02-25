#include "header.h"

int	malloc_forks(t_data *d)
{
	int	i;

	d->mut_forks = malloc(sizeof(pthread_mutex_t) * d->nrfilos);
	if (d->mut_forks == NULL)
		return (print_and_return(1, "Error with mallocing\n"));
	i = 0;
	while (i < d->nrfilos)
	{
		if (pthread_mutex_init(&d->mut_forks[i], NULL) != 0)
			return (print_and_return(1, "Error initializing a mutex\n"));
		i++;
	}
	return (0);
}

int	initiate_mutexes(t_data *data, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < data->nrfilos)
	{
		ph[i].d = data;
		ph[i].id = i;
		i++;
	}
	//if (pthread_mutex_init(&ph->d->mut_time, NULL) != 0)
	//	return (1);
	if (pthread_mutex_init(&ph->d->mut_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&ph->d->mut_protect, NULL) != 0)
		return (1);
	if (malloc_forks(data) != 0)
		return (1);
	return (0);
}

int	loop_create_threads(t_data *d, t_philo *ph, int i)
{
	while (i < d->nrfilos)
	{
		ph[i].new_start_time = get_time();
		ph[i].deadline = ph[i].new_start_time + ph[i].d->time_to_die;
		if (pthread_create(&ph[i].thread,
				NULL, &start_philo, (void *)&ph[i]) != 0)
			return (print_and_return(1, "Error creating a thread\n"));
		i += 1;
	}
	return (0);
}

int	start_threads(t_data *d, t_philo *ph)
{
	if (loop_create_threads(d, ph, 0) != 0)
		return (1);
	if (timer(ph) == 0)
		return (0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo_struct;
	t_data			data;
	struct timeval	t;

	if (check_and_store_arguments(argc, argv, &data) != 0)
		return (1);
	philo_struct = malloc(sizeof(t_philo) * data.nrfilos);
	if (philo_struct == NULL)
		return (print_and_return(1, "Error mallocking philo struct\n"));
	if (initiate_mutexes(&data, philo_struct) != 0)
		return (msg_and_free(philo_struct, &data,
				"Error initializing a mutex", 1));
	gettimeofday(&t, NULL);
	data.startofsession = t.tv_sec * 1000 + t.tv_usec / 1000;
	start_threads(&data, philo_struct);
	join_threads(data, philo_struct);
	free_all(philo_struct, &data);
	return (0);
}
