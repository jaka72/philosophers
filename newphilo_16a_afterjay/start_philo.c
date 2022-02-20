#include "header.h"

void	lock_forks_and_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->d->mutex_forks[ph->id]);

	pthread_mutex_lock(&ph->d->mutex_print);
	message(ph, "has taken a fork", get_time(ph));
	pthread_mutex_unlock(&ph->d->mutex_print);

	pthread_mutex_lock(&ph->d->mutex_forks[(ph->id + 1) % ph->d->nrfilos]);

	pthread_mutex_lock(&ph->d->mutex_print);
	message(ph, "has taken a fork", get_time(ph));
//	pthread_mutex_unlock(&ph->d->mutex_print);
	ph->new_start_time = get_time(ph);
	ph->deadline = ph->new_start_time + ph->d->time_to_die;
//	pthread_mutex_lock(&ph->d->mutex_print);
	message(ph, "is eating", get_time(ph));
	ph->d->count_meals++;
	pthread_mutex_unlock(&ph->d->mutex_print);
	
	//usleep(ph->d->time_to_eat * 1000);
	mysleep(ph->d->time_to_eat);
	pthread_mutex_unlock(&ph->d->mutex_forks[ph->id]);
	pthread_mutex_unlock(&ph->d->mutex_forks[(ph->id + 1) % ph->d->nrfilos]);
}

void	*start_philo(void *philo)
{
	t_philo		*ph;

	ph = philo;
	if (ph->id % 2 == 0)
		usleep(ph->d->time_to_eat * 1000 - 1);
	while (1)
	{
		lock_forks_and_eat(ph);
		pthread_mutex_lock(&ph->d->mutex_print);
		message(ph, "is sleeping", get_time(ph));
		pthread_mutex_unlock(&ph->d->mutex_print);
		//usleep(ph->d->time_to_sleep * 1000);
		mysleep(ph->d->time_to_sleep);
		pthread_mutex_lock(&ph->d->mutex_print);
		message(ph, "is thinking", get_time(ph));
		pthread_mutex_unlock(&ph->d->mutex_print);
		
		pthread_mutex_lock(&ph->d->mutex_death);
		if (ph->d->hasdied == 1)
		{
			pthread_mutex_unlock(&ph->d->mutex_death);
			return (0);
		}
		pthread_mutex_unlock(&ph->d->mutex_death);

	}
}
