#include "newheader.h"

// Does it matter how late it dies, in case it should die?


// What if a struct philo ph[i] is not passed as address into function, 
//   how can you than use mutex_lock in this function with this philo ??
//				mutex_lock(&philo->mutex_time)  with or without & ???

long long milisecs_passed(t_philo *ph)
{
	struct timeval	t;
	long long		milisecs;

	gettimeofday(&t, NULL);
	milisecs = t.tv_sec * 1000 + t.tv_usec / 1000;
	milisecs = milisecs - ph->d->startofsession;
	return (milisecs);
}


void	message(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->d->mutex_print);
	printf("%lld %d %s\n", milisecs_passed(ph), ph->id + 1, str);
	pthread_mutex_unlock(&ph->d->mutex_print);
}


void	free_all(t_philo *ph) // HERE PROBABLY NEEDED PROTECTION FROM DOUBLE FREE !!
{
	int	i;

	pthread_mutex_destroy(&ph->d->mutex_time);
	pthread_mutex_destroy(&ph->d->mutex_print);
	i = 0;
	while (i < ph->d->nrfilos)
	{
		pthread_mutex_unlock(&ph->d->mutex_spoon[i]);
		pthread_mutex_destroy(&ph->d->mutex_spoon[i]);
		i++;
	}
	free(ph->d->mutex_spoon);
	free(ph->d);
	free(ph);
}



int timer(t_philo *ph)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;

	while (1)
	{
		i = 0;
		usleep(100);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].d->mutex_time);
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			current_time = current_time - ph->newtimetodie;

			if (current_time > ph->d->time_to_die)
			{
				message(&ph[i], "has died");
				free_all(ph);
				return (1);
			}
			pthread_mutex_unlock(&ph[i].d->mutex_time);
		}
	}
	return (0);
}






void *start_philo(void *philo)
{
	t_philo			*ph;
	struct timeval	t;

	ph = philo;
	if (ph->id % 2 == 0)
		usleep(500);
	
	while (1)
	{
		pthread_mutex_lock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_lock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);

		// SHALL I PUT THE MESSAGE INSIDE LOCKS?  TO ENSURE THE RIGHT ORDER
		message(ph, "is eating");

		pthread_mutex_lock(&ph->d->mutex_time);// WHY THIS NEEDDS TO BE LOCKED IF IT IS ALREADY INSIDE LOCKS ???
		gettimeofday(&t, NULL);
		pthread_mutex_unlock(&ph->d->mutex_time);

		ph->newtimetodie = t.tv_sec * 1000 + t.tv_usec / 1000;
		//usleep(ph->d->time_to_eat * 1000);
		mysleep(ph->d->time_to_eat);

		pthread_mutex_unlock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_unlock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
	
		//printf("%lld %d is sleeping\n", milisecs_passed(ph), ph->id);
		//message(ph, "is sleeping");
		//usleep(ph->d->time_to_sleep * 1000);
		mysleep(ph->d->time_to_sleep);
	
		//printf("%lld %d is thinking\n", milisecs_passed(ph), ph->id);
		//message(ph, "is thinking");

	}
	return (0);
}



int main(int argc, char **argv)
{
	int		i;
	t_philo	*philo_struct;
	t_data	*data;
	
	// save arguments into data ///////////////////////////////
	if ((data = check_and_save_arguments(argc, argv)) == NULL) // IS THIS MULTIPLE OPERATIONS ???
		return (1);

	
	// save data into philo ///////////////////////////////////
	philo_struct = malloc(sizeof(t_philo) * data->nrfilos);
	if (philo_struct == NULL)
	{
		printf("Error initializing a mutex\n");
		return (1);
	} 
	i = 0;
	while (i < data->nrfilos)
	{
		philo_struct[i].d = data;
		philo_struct[i].id = i;
		i++;
	}


	// init mutexes //////////////////////////////////////////
	if (pthread_mutex_init(&philo_struct->d->mutex_time, NULL) != 0)
	{
		printf("Error creating a thread\n"); // SHOULD HERE THINGS BE FREED ????
		return (1);
	} 

	if (pthread_mutex_init(&philo_struct->d->mutex_print, NULL) != 0)
	{
		printf("Error initializing a mutex\n");
		return (1);
	} 

	i = 0;
	data->mutex_spoon = malloc(sizeof(pthread_mutex_t) * data->nrfilos);
	if (data->mutex_spoon == NULL)
	{
		printf("Error with mallocing\n");
		return (1);
	}

	while (i < data->nrfilos)
	{
		if (pthread_mutex_init(&data->mutex_spoon[i], NULL) != 0)
		{
			printf("Error initializing a mutex\n");
			return (1);
		} 
		i++;
	}


	// start threads /////////////////////////////////////////
	struct timeval	t;
	gettimeofday(&t, NULL);
	data->startofsession = t.tv_sec * 1000 + t.tv_usec / 1000;
	printf("a startofsession %lld \n", philo_struct->d->startofsession);
	//printf("b starofsession %lld \n", philo_struct[3].d->startofsession);

	
	i = 0;
	while (i < data->nrfilos)
	{
		philo_struct[i].newtimetodie = data->startofsession;
		if (pthread_create(&philo_struct[i].thread, NULL, &start_philo, (void*)&philo_struct[i]) != 0)
		{
			printf("Error creating a thread\n");
			return (1);
		} 
		if (pthread_detach(philo_struct[i].thread) != 0)
		{
			printf("Error detaching a thread\n");
			return (1);
		} 
		i++;
	}

	if (timer(philo_struct) == 1)
		return (1);


	return (0);
}
