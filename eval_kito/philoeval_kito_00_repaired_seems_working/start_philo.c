/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_philo.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:14:57 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/23 11:57:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	lock_forks_and_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->d->mutex_forks[ph->id]);
	pthread_mutex_lock(&ph->d->mutex_print);
	message(ph, "has taken a fork", get_time());
	pthread_mutex_unlock(&ph->d->mutex_print);
	pthread_mutex_lock(&ph->d->mutex_forks[(ph->id + 1) % ph->d->nrfilos]);
	pthread_mutex_lock(&ph->d->mutex_print);
	message(ph, "has taken a fork", get_time());
	ph->new_start_time = get_time();
	
	pthread_mutex_lock(&ph->d->mutex_death);
	ph->deadline = ph->new_start_time + ph->d->time_to_die;
	pthread_mutex_unlock(&ph->d->mutex_death);	
	
	message(ph, "is eating", get_time());

	pthread_mutex_lock(&ph->d->mutex_death);
	ph->d->count_meals++;
	if (ph->d->count_meals == ph->d->max_meals_per_philo * ph->d->nrfilos)
		ph->d->mealsreached = 1;
	pthread_mutex_unlock(&ph->d->mutex_death);
	
	pthread_mutex_unlock(&ph->d->mutex_print);
	mysleep(ph->d->time_to_eat);
	pthread_mutex_unlock(&ph->d->mutex_forks[ph->id]);
	pthread_mutex_unlock(&ph->d->mutex_forks[(ph->id + 1) % ph->d->nrfilos]);
	return (0);
}

void	*start_philo(void *philo)
{
	t_philo		*ph;

	ph = philo;
	if (ph->id % 2 == 0)
		mysleep(ph->d->time_to_eat - 1);
	while (1)
	{
		if (lock_forks_and_eat(ph) == 1)
			return (0);
		pthread_mutex_lock(&ph->d->mutex_print);
		message(ph, "is sleeping", get_time());
		pthread_mutex_unlock(&ph->d->mutex_print);
		mysleep(ph->d->time_to_sleep);
		pthread_mutex_lock(&ph->d->mutex_print);
		message(ph, "is thinking", get_time());
		pthread_mutex_unlock(&ph->d->mutex_print);
		
		pthread_mutex_lock(&ph->d->mutex_death);
		if (ph->d->hasdied == 1 || ph->d->mealsreached == 1)
		{
			pthread_mutex_unlock(&ph->d->mutex_death);
			return (0);
		}
		pthread_mutex_unlock(&ph->d->mutex_death);
	}
	return (0);
}
