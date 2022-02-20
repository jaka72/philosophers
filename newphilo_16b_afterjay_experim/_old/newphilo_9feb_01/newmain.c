#include "newheader.h"



void *start_philo(void *philo)
{
	t_philo			*ph;
	long long	time;

	ph = philo;
//	if (ph->id % 2 == 0)
//		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&ph->d->mutex_spoon[ph->id]);
		// printf("  id%d after A),   %lld\n", ph->id, get_time(ph) - ph->new_start_time);
		message(ph, "has taken fork", get_time(ph));
		pthread_mutex_lock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
		// printf("  id%d after B)    %lld\n", ph->id, get_time(ph) - ph->new_start_time);
		message(ph, "has taken fork", get_time(ph));
		
		time = get_time(ph);
		ph->new_start_time = time;
		ph->deadline = time + ph->d->time_to_die;
		message(ph, "is eating", time);

		usleep(ph->d->time_to_eat * 1000);
		//mysleep(ph->d->time_to_sleep, time);
		pthread_mutex_unlock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_unlock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
		time = get_time(ph);
		//message(ph, "is sleeping", time);
		usleep(ph->d->time_to_sleep * 1000);
		//mysleep(ph->d->time_to_sleep, time);
		time = get_time(ph);
		//message(ph, "is thinking", time);
	}
	return (0);
}



int	malloc_spoons(t_data *d)
{
	int	i;

	d->mutex_spoon = malloc(sizeof(pthread_mutex_t) * d->nrfilos);
	if (d->mutex_spoon == NULL)
	{
		printf("Error with mallocing\n");
		return (1);
	}
	i = 0;
	while (i < d->nrfilos)
	{
		if (pthread_mutex_init(&d->mutex_spoon[i], NULL) != 0)
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
	{
		printf("Error creating a thread\n"); // SHOULD HERE THINGS BE FREED ????
		return (1);
	} 
	if (pthread_mutex_init(&ph->d->mutex_print, NULL) != 0)
	{
		printf("Error initializing a mutex\n");
		return (1);
	} 
	if (malloc_spoons(data) == 1)
		return (1);
	return (0);
}


int	start_threads(t_data *d, t_philo *ph)
{
	int	i;

	i = 0;	// EVERY EVEN ID //////////////////////
	while (i < d->nrfilos)
	{
		//ph[i].new_start_time = d->startofsession;
		ph[i].new_start_time = get_time(ph);
		
		//ph[i].deadline = d->startofsession + ph[i].d->time_to_die;
		ph[i].deadline = ph[i].new_start_time + ph[i].d->time_to_die;
		if (pthread_create(&ph[i].thread, NULL, &start_philo, (void*)&ph[i]) != 0)
		{
			printf("Error creating a thread\n");
			return (1);
		} 
		// if (pthread_detach(ph[i].thread) != 0)
		// {
		// 	printf("Error detaching a thread\n");
		// 	return (1);
		// }
		//pthread_join(ph[i].thread, NULL);
		usleep(10);
		i += 2;
	}


	i = 1;	 	// EVERY ODD ID ///////////////////////
	while (i < d->nrfilos)
	{
		//ph[i].new_start_time = d->startofsession;
		ph[i].new_start_time = get_time(ph);
		
		//ph[i].deadline = d->startofsession + ph[i].d->time_to_die;
		ph[i].deadline = ph[i].new_start_time + ph[i].d->time_to_die;
		if (pthread_create(&ph[i].thread, NULL, &start_philo, (void*)&ph[i]) != 0)
		{
			printf("Error creating a thread\n");
			return (1);
		} 
		// if (pthread_detach(ph[i].thread) != 0)
		// {
		// 	printf("Error detaching a thread\n");
		// 	return (1);
		// }
		//pthread_join(ph[i].thread, NULL);
		usleep(10);
		i += 2;
	}


	if (timer(ph) == 1)
		return (1);


	i = 0;
	while (i < d->nrfilos)
	{
		if (pthread_detach(ph[i].thread) != 0)
		{
			printf("Error joining a thread\n");
			return (1);
		}
		i++;
	}


	// i = 0;
	// while (i < d->nrfilos)
	// {
	// 	if (pthread_join(ph[i].thread, NULL) != 0)
	// 	{
	// 		printf("Error joining a thread\n");
	// 		return (1);
	// 	}
	// 	i++;
	// }

	return (0);
}






int main(int argc, char **argv)
{
	//int		i;
	t_philo	*philo_struct;
	t_data	*data;
	struct timeval	t;
	



	data = check_and_save_arguments(argc, argv);
	if (data == NULL)
		return (1);
	philo_struct = malloc(sizeof(t_philo) * data->nrfilos);
	if (philo_struct == NULL)
	{
		printf("Error initializing a mutex\n");
		return (1);
	} 
	if (initiate_mutexes(data, philo_struct) == 1)
		return (1);
	gettimeofday(&t, NULL);
	data->startofsession = t.tv_sec * 1000 + t.tv_usec / 1000;

	// if (timer(philo_struct) == 1)
	// 	return (1);

	start_threads(data, philo_struct);


	//printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

	// if (timer(philo_struct) == 1)
	// 	return (1);
	return (0);
}

