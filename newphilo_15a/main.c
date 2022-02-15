#include "header.h"

int	malloc_forks(t_data *d)
{
	int	i;

	d->mutex_forks = malloc(sizeof(pthread_mutex_t) * d->nrfilos);
	if (d->mutex_forks == NULL)
	{
		printf("Error with mallocing\n");
		return (1);
	}
	i = 0;
	while (i < d->nrfilos)
	{
		if (pthread_mutex_init(&d->mutex_forks[i], NULL) != 0)
		{
			printf("Error initializing a mutex\n");
			return (1);
		}
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
	if (pthread_mutex_init(&ph->d->mutex_time, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&ph->d->mutex_print, NULL) != 0)
		return (1);
	if (malloc_forks(data) != 0)
		return (1);
	return (0);
}

int	loop_create_threads(t_data *d, t_philo *ph, int i)
{
	while (i < d->nrfilos)
	{
		ph[i].new_start_time = get_time(ph);
		ph[i].deadline = ph[i].new_start_time + ph[i].d->time_to_die;
		if (pthread_create(&ph[i].thread,
				NULL, &start_philo, (void *)&ph[i]) != 0)
		{
			printf("Error creating a thread\n");
			return (1);
		}
		usleep(10);
		i += 1;
	}
	return (0);
}

int	start_threads(t_data *d, t_philo *ph)
{
	int	i;

	if (loop_create_threads(d, ph, 0) != 0)
		return (msg_and_free(ph, d, "", 1));
	if (timer(ph, d) == 1)
		return (1);
	i = 0;
	while (i < d->nrfilos)
	{
		if (pthread_join(ph[i].thread, NULL) != 0)
		{
			printf("Error joining a thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo_struct;
	t_data			*data;
	struct timeval	t;

	data = check_and_store_arguments(argc, argv);
	if (data == NULL)
		return (1);
	philo_struct = malloc(sizeof(t_philo) * data->nrfilos);
	if (philo_struct == NULL)
	{
		printf("Error mallocking philo struct\n");
		free(data);
		free(philo_struct);
		return (1);
	}
	if (initiate_mutexes(data, philo_struct) != 0)
		return (msg_and_free(philo_struct, data,
				"Error initializing a mutex", 1));
	gettimeofday(&t, NULL);
	data->startofsession = t.tv_sec * 1000 + t.tv_usec / 1000;
	start_threads(data, philo_struct);
	return (0);
}
