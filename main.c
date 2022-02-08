#include "philo.h"

void	print_msg(t_philo *ph, char *msg)
{
	printf("%ld %d %s", milisecs_passed(ph), ph->philo_id, msg);
}

// int	timer(void *philo)
// {
// 	t_philo			*ph;
// 	unsigned long	reached; 
// 	int				i;

// 	ph = philo;
// 	while (1)
// 	{
// 		i = 0;
// 		//usleep(2000);
// 		while (i < ph->d->nrfilos)
// 		{
// 			pthread_mutex_lock(&ph[i].mutex_time);
// 			//reached = milisecs_passed(ph);
// 			reached = milisecs_passed(ph);
// 			if (reached > ph->deadline)
// 			{
// 				printf("%ld %d has died\n", reached, i + 1);
// 				return (1);
// 				//exit(0);
// 			}
// 			pthread_mutex_unlock(&ph[i].mutex_time);
// 			i++;
// 		}
// 		usleep(500);
// 		//mysleep(1);
// 	}
// 	return (0);
// }


int	newtimer(t_philo *philo)
{
	int				i;
	struct timeval	time;
	unsigned long long	currenttime;

	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < philo->d->nrfilos)
		{
			pthread_mutex_lock(&philo[i].mutex_time);
			gettimeofday(&time, NULL);
			currenttime = time.tv_sec * 1000 + time.tv_usec / 1000;

			// if (i + 1 == 1)
			// 	printf("currenttime %lld   newtimetodie %lld\n", currenttime, philo->newtimetodie);

			currenttime = currenttime - philo[i].newtimetodie;


			if (currenttime > philo->d->time_to_die)
			{
				printf("currenttime %lld   newtimetodie %lld\n", currenttime, philo->d->time_to_die);
				print_msg(philo, "has died\n");	
				return (1);
			}

			pthread_mutex_unlock(&philo[i].mutex_time);
		}
	}
	return (0);
}



// void	calc_deadline(void *philo_struct)
// {
// 	t_philo	*ph;

// 	ph = philo_struct;
// 	//ph[ph->philo_id].time_started_eating = milisecs_passed(ph->startofsession);
// 	ph[ph->philo_id].time_started_eating = milisecs_passed(ph);
// 	ph->deadline = ph[ph->philo_id].time_started_eating + ph->d->time_to_die;
// 	//ph->d->deadlines[id] = ph->d->time_started_eating[id] + ph->d->time_to_die;
	
// 	//ph->d->old_times_eaten[id] = ph->d->new_times_eaten[id];
// 	//ph->d->new_times_eaten[id]++;
// }


/*
void	calc_deadline(void *philo_struct)
{
	t_philo	*ph;

	ph = philo_struct;
	ph->time_started_eating = milisecs_passed(ph);
	ph->deadline = ph->time_started_eating + ph->d->time_to_die;
	
	//ph->d->old_times_eaten[id] = ph->d->new_times_eaten[id];
	//ph->d->new_times_eaten[id]++;
}
*/



void *start_thread(void *philo_struct)
{
	int				id;
	int				i;
	t_philo			*ph;
	struct timeval	newtime;

	ph = philo_struct;
	id = ph->philo_id;
	
	i = 0;
	if (id % 2 == 0)
	 	usleep(100);

	//while (i < 3)
	while (1)
	{
		//printf("     a)\n");
		pthread_mutex_lock(&ph->d->fork_mutex[id]);
		//printf("     %ld %d has taken fork %d\n", milisecs_passed(ph->startofsession), id + 1, (id));
		pthread_mutex_lock(&ph->d->fork_mutex[(id + 1) % ph->d->nrfilos]);
		//printf("     %ld %d has taken fork %d\n", milisecs_passed(ph->startofsession), id + 1, ((id + 1) % ph->d->nrfilos));


		//pthread_mutex_lock(&ph->mutex_time);
		//calc_deadline(ph);
		//pthread_mutex_unlock(&ph->mutex_time);

		//printf("     b)\n");

//		pthread_mutex_lock(&ph->mutex_time);
//		ph->time_started_eating = milisecs_passed(ph);
//		ph->deadline = ph->time_started_eating + ph->d->time_to_die;
//		pthread_mutex_unlock(&ph->mutex_time);


		pthread_mutex_lock(&ph->mutex_time);
		gettimeofday(&newtime, NULL);
		pthread_mutex_unlock(&ph->mutex_time);


		/* printf("%lld %d is eating ... deadline %ld\n", \
		ph->time_started_eating, id + 1, ph->deadline); */
		
		//printf("%ld %d is eating\n", milisecs_passed(ph), id + 1);
		print_msg(ph, "is eating\n");
		ph->newtimetodie = newtime.tv_sec * 1000 + newtime.tv_usec / 1000;
		//printf("newtimetodie %lld \n", ph->newtimetodie);

		mysleep(ph->d->time_to_eat); // 10000 = 10 milisec,     100000 = 100 milisec
		
		pthread_mutex_unlock(&ph->d->fork_mutex[id]);
		pthread_mutex_unlock(&ph->d->fork_mutex[(id + 1) % ph->d->nrfilos]);

		//printf("%ld %d is sleeping\n", milisecs_passed(ph), id + 1);
		mysleep(ph->d->time_to_sleep);
		
		//printf("%d is thinking\n", id);
		i++;
	}
	return (0);
}


void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->d->nrfilos)
	{
		pthread_mutex_unlock(&philo->d->fork_mutex[i]);
		pthread_mutex_destroy(&philo->d->fork_mutex[i]);

		pthread_mutex_destroy(&philo[i].mutex_time);

		//pthread_detach(philo[i].philo_thread); // IS THIS NECESSARY ??
		// pthread_join(philo[i].philo_thread, NULL); // SHOULD THIS BE IMMEDIATELY AFTER CREATE, IN SAME LOOP  ???
		i++;
	}
}

void	assign_data_to_philo(t_philo *ph, t_data *data, int *i)
{
	//i = 0;
	//while (i < ph->d->nrfilos)
	//{
		ph[*i].philo_id = *i;
		ph[*i].d = data;
		ph[*i].deadline = data->time_to_die;
		ph[*i].time_started_eating = 0;
		//philo_struct[i].startofsession = data->startofsession;
		i++;
	//}
}


int main(int argc, char *argv[])
{
	int				i;
	t_philo			*philo_struct;
	t_data			*data;		// SHOULD THIS BE BETTER DECLARED AS POINTER ??

	data = malloc(sizeof(t_data));
		// check error
	if (check_and_save_arguments(argc, argv, data) == 1)
		return (1);

	philo_struct = malloc(sizeof(t_philo) * data->nrfilos);
		// check error

	init_mutexes(data, philo_struct);	// malloc mutexfork * nrfilos, then inits the in a loop 



	// FIRST I USED LARGER NUMBER, INCLUDED MICROSECONDS:  1644063052830942
	// 													1644063052830
	gettimeofday(&philo_struct->start, NULL);
	//data.time_start_of_session = philo_struct->start.tv_sec * 1000000 + philo_struct->start.tv_usec;
	data->startofsession = philo_struct->start.tv_sec * 1000 + philo_struct->start.tv_usec / 1000;
	printf("DATA.TIME_start_of_session:    %lld\n", data->startofsession);


	i = 0;
	while (i < data->nrfilos) 
	{
		assign_data_to_philo(philo_struct, data, &i);
		// philo_struct[i].startofsession = startofsession;
		//printf("loop create: ID%i \n", i+1);


		//pthread_create(&philo_thread[i], NULL, start_thread, (void*)&philo_struct[i]);
		pthread_create(&philo_struct[i].philo_thread, NULL, &start_thread, (void*)&philo_struct[i]);
			// check errors, also maybe use pthread_detach

		pthread_detach(philo_struct[i].philo_thread); // IS THIS NECESSARY ??


		//pthread_join(philo_struct[i].philo_thread, NULL); // SHOULD THIS BE HERE IN SAME LOOP  ???
	
		usleep(100);
		i++;
	}

	if (newtimer(philo_struct) == 1)
	{
		free_all(philo_struct);
		return (1);
	}


	// i = 0;
	// while (i < atoi(argv[1]))
	// {
	// 	pthread_mutex_destroy(&philo_struct[i].d->fork_mutex[i]);
	// 	pthread_detach(philo_struct[i].philo_thread); // IS THIS NECESSARY ??
	// 	pthread_join(philo_struct[i].philo_thread, NULL);
	// 	i++;
	// }
	return (0);
}



