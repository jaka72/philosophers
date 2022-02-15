#include "header.h"

int	has_died(t_philo *ph, long long current_time)
{
	if (current_time > ph->deadline)
	{
		pthread_mutex_lock(&ph->d->mutex_print);
		printf("%lld %d died\n", current_time - ph->d->startofsession,
			ph->id + 1);
		pthread_mutex_unlock(&ph->d->mutex_print);
		return (1);
	}
	if (ph->d->count_meals == ph->d->max_meals_per_philo * ph->d->nrfilos)
	{
		pthread_mutex_lock(&ph->d->mutex_print);
		printf("Reached max meals (%d) per philosopher.\n",
			ph->d->max_meals_per_philo);
		pthread_mutex_unlock(&ph->d->mutex_print);
		return (1);
	}
	return (0);
}

int	timer(t_philo *ph, t_data *d)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;

	d->count_meals = d->count_meals;

	while (1)
	{
		i = 0;
		usleep(2000);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].d->mutex_time);
			gettimeofday(&t, NULL);			
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			if (has_died(&ph[i], current_time) == 1)
			{
				msg_and_free(ph, d, "", 1);
				//system("leaks philo");
				return (1);
			}
			pthread_mutex_unlock(&ph[i].d->mutex_time);
			i++;
		}
	}
	return (0);
}
