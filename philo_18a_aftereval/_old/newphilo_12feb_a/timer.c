#include "newheader.h"


// int	has_died(t_philo *ph, long long current_time, long long new_start)
int	has_died(t_philo *ph, long long current_time)
{
	if (current_time > ph->deadline)
	{
		pthread_mutex_lock(&ph->d->mutex_print);
		//printf("     current time %lld,   deadline %lld, diff %lld\n", current_time - ph->d->startofsession, \ ph->deadline - ph->d->startofsession, ph->deadline - current_time);
		//printf("     current time - newstart = %lld\n", current_time - new_start);
		printf("%lld %d has died\n", milisecs_passed(ph), ph->id);
		pthread_mutex_unlock(&ph->d->mutex_print);

		//free_all(ph);
		return (1);
	}
	if (ph->d->count_meal_rounds == ph->d->nrfilos)
	{
		pthread_mutex_lock(&ph->d->mutex_print);
		printf("Reached max meals (%d) per philosopher.\n", ph->d->max_meals);
		pthread_mutex_unlock(&ph->d->mutex_print);

		return (1);
	}
	return (0);
}


int timer(t_philo *ph)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;

	while (1)
	{
		i = 0;
		usleep(2000);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].d->mutex_time);
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			// if (has_died(&ph[i], current_time, ph[i].new_start_time) == 1)
			if (has_died(&ph[i], current_time) == 1)
				return (1);
			pthread_mutex_unlock(&ph[i].d->mutex_time);
			
			i++;
		}
	}
	return (0);
}
