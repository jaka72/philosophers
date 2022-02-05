#include "philo.h"

void	*timer(void *philo)
{
	t_philo		*ph;
	long int	reached; 
	int			i;

	ph = philo;
	while (1)
	{
		i = 0;
		reached = milisecs_passed(ph);
		while (i < ph->d->nrfilos)
		{
			//reached = milisecs_passed(ph);
			if (reached > ph->d->deadlines[i]) 
			{
				printf("%ld %d has died\n", reached, i + 1);
				//return (0);
				exit(0);
			}
			i++;
		}
		usleep(100);
		//mysleep(1);
	}
	return (0);
}




void	calc_deadline(void *philo_struct)
{
	t_philo	*ph;
	int		id;

	ph = philo_struct;
	id = ph->philo_id;
	ph->d->time_started_eating[id] = milisecs_passed(ph);	
	ph->d->deadlines[id] = ph->d->time_started_eating[id] + ph->d->time_to_die;
	//ph->d->old_times_eaten[id] = ph->d->new_times_eaten[id];
	//ph->d->new_times_eaten[id]++;
}


void *start_thread(void *philo_struct)
{
	int		id;
	int		i;
	t_philo	*ph;

	ph = philo_struct;
	id = ph->philo_id;
	

	i = 0;
	if (id % 2 == 0)
	 	usleep(1000);

	//while (i < 3)
	while (1)
	{
		pthread_mutex_lock(&ph->d->fork_mutex[id]);
		printf("     %ld %d has taken fork %d\n", milisecs_passed(ph), id + 1, (id));
		pthread_mutex_lock(&ph->d->fork_mutex[(id + 1) % ph->d->nrfilos]);
		printf("     %ld %d has taken fork %d\n", milisecs_passed(ph), id + 1, ((id + 1) % ph->d->nrfilos));

		calc_deadline(ph);

		// ph->d->time_started_eating[id] = milisecs_passed(ph);
		
		// ph->d->deadlines[id] = ph->d->time_started_eating[id] + ph->d->time_to_die;
		// ph->d->old_times_eaten[id] = ph->d->new_times_eaten[id];
		// ph->d->new_times_eaten[id]++;
		
		/*printf("%ld %d is eating ... deadline %ld\n", \
		ph->d->time_started_eating[id], id + 1, ph->d->deadlines[id]); */
		
		printf("%ld %d is eating\n", milisecs_passed(ph), id + 1);
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



int main(int argc, char *argv[])
{
	int				i;
	t_philo			*philo_struct;
	pthread_t		*philo_thread;	// THIS COULD BE A MEMBER INSIDE OF PHILO STRUCT
	t_data			data;		// SHOULD THIS BE BETTER DECLARED AS POINTER ??
	pthread_t		timer_thread[1];

	if (check_and_save_arguments(argc, argv, &data) == 1)
		return (1);

	make_arrays_and_philos(&data);

	philo_thread = malloc(sizeof(pthread_t) * data.nrfilos);
	philo_struct = malloc(sizeof(t_philo) * data.nrfilos);
		// check error

	// ASSIGN DATA TO EACH philo[i]
	i = 0;
	while (i < data.nrfilos)
	{
		philo_struct[i].philo_id = i;
		philo_struct[i].d = &data;
		i++;
	}


	// I NEED TO CHANGE EVERYWHERE, WHERE I USE time_start_of_session
	// NOW I USE LARGER NUMBER, INCLUDED MICROSECONDS:  1644063052830942
	// 													1644063052830
	gettimeofday(&philo_struct->start, NULL);
	//data.time_start_of_session = philo_struct->start.tv_sec * 1000000 + philo_struct->start.tv_usec;
	data.time_start_of_session = philo_struct->start.tv_sec * 1000 + philo_struct->start.tv_usec / 1000;

	


	pthread_create(&timer_thread[0], NULL, timer, (void*)&philo_struct[0]); // ONLY THE FIRST STRUCT HAS TIMER ??
														// MAYBE I SHOULD CREATE A SEPARATE STRUCT FOR TIMER 



	i = 0;
	while (i < data.nrfilos) 
	{
		pthread_create(&philo_thread[i], NULL, start_thread, (void*)&philo_struct[i]);
			// check errors, also use pthread_detach
		usleep(1);
		i++;
	}


	i = 0;
	while (i < atoi(argv[1]))
	{
		pthread_mutex_destroy(&philo_struct[i].d->fork_mutex[i]);
		pthread_join(philo_thread[i], NULL);
		i++;
	}
	pthread_join(timer_thread[0], NULL);
	return (0);
}



