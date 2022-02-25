#include "newheader.h"

// Does it matter how late it dies, in case it should die?


// What if a struct philo ph[i] is not passed as address into function, 
//   how can you than use mutex_lock in this function with this philo ??
//				mutex_lock(&philo->mutex_time)  with or without & ???


// MYSLEEP() CAUSES THAT TIME IS UPDATED, SO IT NEVER DIES IN CASE OF SHORT TIMETODIE
// NOW WITH USLEEP() I GET floating point exeption, WHEN IT SHOULD DIE 4 310 200 200 
// PROBABLY THERE IS ALSO ISSUE WITH TIMER - HOW DOES IT KNOW WHICH PHILOSOPHER IS BEING CHECKED ???

long long milisecs_passed(t_philo *ph)
{
	struct timeval	t;
	long long		milisecs;


	//pthread_mutex_lock(&ph->d->mutex_time);
	gettimeofday(&t, NULL);
	milisecs = t.tv_sec * 1000 + t.tv_usec / 1000;
	milisecs = milisecs - ph->d->startofsession;
	//pthread_mutex_lock(&ph->d->mutex_time);

	return (milisecs);
}


void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	pthread_mutex_lock(&ph->d->mutex_print);
	//printf("%lld %d %s\n", milisecs_passed(ph), ph->id + 1, str);
	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
	
	mspassed = time - ph->d->startofsession;
	
	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
	printf("%lld %d %s ... deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
	
	
	
	
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



int	has_died(t_philo *ph, unsigned long long current_time, unsigned long long new_start)
{
	//printf("  current %lld\n  newstart %lld\n", current_time, ph->new_start_time);


	//if ( (current_time - ph->new_start_time)  > ph->d->time_to_die)
	if (current_time > ph->deadline)
	//if (current_time > (ph->new_start_time + ph->d->time_to_die))
	{
		pthread_mutex_lock(&ph->d->mutex_print);
		//message(ph, "has died");
		//printf("     current time %lld,   newstart %lld\n", current_time, new_start);
		printf("     current time %lld,   deadline %lld, diff %lld\n", current_time - ph->d->startofsession, \
					ph->deadline - ph->d->startofsession, ph->deadline - current_time);
		printf("     current time - newstart = %lld\n", current_time - new_start);
		printf("%lld %d has died\n", milisecs_passed(ph), ph->id);
		pthread_mutex_unlock(&ph->d->mutex_print);

		//free_all(ph);
		return (1);
	}
	return (0);
}


int timer(t_philo *ph)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;

	//ph->d->time_to_die += 8;
	while (1)
	{
		i = 0;
		usleep(2000);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].d->mutex_time);
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			//current_time = current_time - ph->new_start_time;  // !!!!!!!!!!!!!!!!!!
			
			
			//current_time = current_time - ph[i].new_start_time;

			//printf(" %d", ph[i].id);

			// if (current_time > ph->d->time_to_die)
			// {
			// 	//pthread_mutex_lock(&ph[i].d->mutex_print);
			// 	message(&ph[i], "has died");
			// 	//pthread_mutex_unlock(&ph[i].d->mutex_print);

			// 	//free_all(ph);  // here maybe too early to free ????
			// 	return (1);
			// }

			if (has_died(&ph[i], current_time, ph[i].new_start_time) == 1)
				return (1);

			pthread_mutex_unlock(&ph[i].d->mutex_time);
			i++;	 // THIS WAS MISSING !!!!!
		}
	}
	return (0);
}


/*
0 wait			1 wait			2
1 continue		2 continue		4	
2 wait			3 wait			1
3 continue		4 continue		3
*/






void *start_philo(void *philo)
{
	t_philo			*ph;
	struct timeval	t;
	unsigned long long	time;

	ph = philo;
	if (ph->id % 2 == 0)
	{
		//printf("     %d is waiting\n", ph->id);
		usleep(2000);
	} else {
		; //printf("     %d continue\n", ph->id);
	}

	while (1)
	{
		//printf("        a%d", ph->id);
		pthread_mutex_lock(&ph->d->mutex_spoon[ph->id]);
		//printf("  b%d", ph->id);
		pthread_mutex_lock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
		//printf("  c%d", ph->id);

		// SHALL I PUT THE MESSAGE INSIDE LOCKS?  TO ENSURE THE RIGHT ORDER
		// message(ph, "is eating");

		pthread_mutex_lock(&ph->d->mutex_time);// WHY THIS NEEDDS TO BE LOCKED IF IT IS ALREADY INSIDE LOCKS ???
		gettimeofday(&t, NULL);
		pthread_mutex_unlock(&ph->d->mutex_time);
		//printf("  d%d", ph->id);

		//ph->new_start_time = t.tv_sec * 1000 + t.tv_usec / 1000; // !!!

		time = t.tv_sec * 1000 + t.tv_usec / 1000;

		ph->deadline = time + ph->d->time_to_die;

		//printf("  e%d\n", ph->id);
		//printf("first deadline %d  %lld\n", ph->id + 1, ph->deadline - ph->d->startofsession);
		message(ph, "is eating", time);

		usleep(ph->d->time_to_eat * 1000);
		//mysleep(ph->d->time_to_eat, ph->new_start_time);

		pthread_mutex_unlock(&ph->d->mutex_spoon[ph->id]);
		pthread_mutex_unlock(&ph->d->mutex_spoon[(ph->id + 1) % ph->d->nrfilos]);
	
		//printf("%lld %d is sleeping\n", milisecs_passed(ph), ph->id);
		//message(ph, "is sleeping");
		usleep(ph->d->time_to_sleep * 1000);
		// pthread_mutex_lock(&ph->d->mutex_time);// WHY THIS NEEDDS TO BE LOCKED IF IT IS ALREADY INSIDE LOCKS ???
		// gettimeofday(&t, NULL);
		// pthread_mutex_unlock(&ph->d->mutex_time);
		// ph->new_start_time = t.tv_sec * 1000 + t.tv_usec / 1000; // !!!!!!!!!!!!
		// mysleep(ph->d->time_to_sleep, ph->new_start_time);
	
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

	data->mutex_spoon = malloc(sizeof(pthread_mutex_t) * data->nrfilos);
	if (data->mutex_spoon == NULL)
	{
		printf("Error with mallocing\n");
		return (1);
	}

	i = 0;
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
	//printf("a startofsession %lld \n", philo_struct->d->startofsession);
	//printf("b starofsession %lld \n", philo_struct[3].d->startofsession);

	


	i = 0;
	while (i < data->nrfilos)
	{
		philo_struct[i].new_start_time = data->startofsession;
		philo_struct[i].deadline = data->startofsession + philo_struct[i].d->time_to_die;

		//printf("Create thread %d\n", philo_struct[i].id);

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
		//pthread_join(philo_struct[i].thread, NULL);
		//usleep(1000);
		i++;
	}

	if (timer(philo_struct) == 1)
		return (1);

	// i = 0;
	// while (i < data->nrfilos)
	// {
	// 	if (pthread_join(philo_struct[i].thread, NULL) != 0)
	// 	{
	// 		printf("Error joining a thread\n");
	// 		return (1);
	// 	}
	// 	i++;
	// }


	// if (timer(philo_struct) == 1)
	// 	return (1);


	return (0);
}
