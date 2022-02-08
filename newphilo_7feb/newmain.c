#include "newheader.h"


long long milisecs_passed(t_philo *ph)
{
	struct timeval	t;
	long long		milisecs;

	gettimeofday(&t, NULL);
	milisecs = t.tv_sec * 1000 + t.tv_usec / 1000;
	milisecs = milisecs - ph->d->startofsession;
	return (milisecs);
}


int timer(t_philo *ph)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;

	// printf("f starofsession %lld \n", ph->d->startofsession);
	// printf("g starofsession %lld \n", ph[0].d->startofsession);


	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].mutex_time);
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			current_time = current_time - ph->newtimetodie;

			if (current_time > ph->d->time_to_die)
			{
				printf("%lld %d has died\n", milisecs_passed(ph), ph[i].id);
				return (1);
			}

			pthread_mutex_unlock(&ph[i].mutex_time);
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
		usleep(1000);
	
	while (1)
	{
		pthread_mutex_lock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_lock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);

		// Maybe add separate locks for each writting
		printf("%lld %d is eating\n", milisecs_passed(ph), ph->id);

		pthread_mutex_lock(&ph->mutex_time);
		gettimeofday(&t, NULL);
		pthread_mutex_unlock(&ph->mutex_time);

		ph->newtimetodie = t.tv_sec * 1000 + t.tv_usec / 1000;
		usleep(ph->d->time_to_eat * 1000);

		pthread_mutex_unlock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_unlock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
	
		//printf("%lld %d is sleeping\n", milisecs_passed(ph), ph->id);
		usleep(ph->d->time_to_sleep * 1000);
	
		//printf("%lld %d is thinking\n", milisecs_passed(ph), ph->id);
	}
	return (0);
}



int main(int argc, char **argv)
{
	int		i;
	t_philo	*philo_struct;
	t_data	*data;


	
	// save arguments into data ///////////////////////////////
	if ((data = check_and_save_arguments(argc, argv)) == NULL)
		return (1);

	
	// save data into philo ///////////////////////////////////
	philo_struct = malloc(sizeof(t_philo) * data->nrfilos);
		// check error
	i = 0;
	while (i < data->nrfilos)
	{
		philo_struct[i].d = data;
		philo_struct[i].id = i;
		philo_struct[i].newtimetodie = 0; // ????? 
		i++;
		// MISSING newtimetodie, IS DEFINED THEIN LOOP start_threads
		// BECAUSE THE VALUE IS HERE NOT KNOWN YET
	}


	// init mutexes //////////////////////////////////////////
	pthread_mutex_init(&philo_struct->mutex_time, NULL); // WITHOUT & ???
		// check error
	i = 0;
	data->mutex_spoon = malloc(sizeof(pthread_mutex_t) * data->nrfilos);
		// check error
	while (i < data->nrfilos)
	{
		pthread_mutex_init(&data->mutex_spoon[i], NULL);
			// check error
		i++;
	}


	// start threads /////////////////////////////////////////
	struct timeval	t;
	gettimeofday(&t, NULL);
	data->startofsession = t.tv_sec * 1000 + t.tv_usec / 1000;
	printf("a starofsession %lld \n", philo_struct->d->startofsession);
	printf("b starofsession %lld \n", philo_struct[3].d->startofsession);

	i = 0;
	while (i < data->nrfilos)
	{
		philo_struct[i].newtimetodie = data->startofsession;
		pthread_create(&philo_struct[i].thread, NULL, &start_philo, (void*)&philo_struct[i]);
			// check error
		pthread_detach(philo_struct[i].thread);
			// check error
		i++;
	}

	if (timer(philo_struct) == 1)
		return (1);

	return (0);
}
