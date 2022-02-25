/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_philo.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaka <jaka@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 12:05:24 by jaka          #+#    #+#                 */
/*   Updated: 2022/02/25 12:05:36 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	start_eating(t_philo *ph)
{
	ph->new_start_time = get_time();
	pthread_mutex_lock(&ph->d->mut_protect);
	ph->deadline = ph->new_start_time + ph->d->time_to_die;
	pthread_mutex_unlock(&ph->d->mut_protect);
	message(ph, "is eating", get_time());
	ph->d->count_meals++;
	if (ph->d->count_meals == ph->d->max_meals_per_philo * ph->d->nrfilos)
	{	
		pthread_mutex_lock(&ph->d->mut_protect);
		ph->d->mealsreached = 1;
		pthread_mutex_unlock(&ph->d->mut_protect);
	}
}

int	lock_forks_and_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->d->mut_forks[ph->id]);
	pthread_mutex_lock(&ph->d->mut_print);
	message(ph, "has taken a fork", get_time());
	pthread_mutex_unlock(&ph->d->mut_print);
	if (ph->d->nrfilos == 1)
	{
		pthread_mutex_unlock(&ph->d->mut_forks[ph->id]);
		mysleep(ph->d->time_to_die);
		return (0);
	}
	pthread_mutex_lock(&ph->d->mut_forks[(ph->id + 1) % ph->d->nrfilos]);
	pthread_mutex_lock(&ph->d->mut_print);
	message(ph, "has taken a fork", get_time());
	start_eating(ph);
	pthread_mutex_unlock(&ph->d->mut_print);
	mysleep(ph->d->time_to_eat);
	pthread_mutex_unlock(&ph->d->mut_forks[ph->id]);
	pthread_mutex_unlock(&ph->d->mut_forks[(ph->id + 1) % ph->d->nrfilos]);
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
		pthread_mutex_lock(&ph->d->mut_print);
		message(ph, "is sleeping", get_time());
		pthread_mutex_unlock(&ph->d->mut_print);
		mysleep(ph->d->time_to_sleep);
		pthread_mutex_lock(&ph->d->mut_print);
		message(ph, "is thinking", get_time());
		pthread_mutex_unlock(&ph->d->mut_print);
		pthread_mutex_lock(&ph->d->mut_protect);
		if (ph->d->hasdied == 1 || ph->d->mealsreached == 1)
		{
			pthread_mutex_unlock(&ph->d->mut_protect);
			return (0);
		}
		pthread_mutex_unlock(&ph->d->mut_protect);
	}
	return (0);
}
