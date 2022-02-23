/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:15:01 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/23 13:29:50 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	has_died(t_philo *ph, long long current_time)
{
	pthread_mutex_lock(&ph->d->mutex_death);
	if (current_time > ph->deadline)
	{
		ph->d->hasdied = 1;
		//pthread_mutex_lock(&ph->d->mutex_print); // this seems to be redundant, works fine
		printf("%lld %d died\n", current_time - ph->d->startofsession,
			ph->id + 1);
		//pthread_mutex_unlock(&ph->d->mutex_print);
		pthread_mutex_unlock(&ph->d->mutex_death);

		return (1);
	}
	pthread_mutex_unlock(&ph->d->mutex_print);
	pthread_mutex_unlock(&ph->d->mutex_death);
	
	pthread_mutex_lock(&ph->d->mutex_death);
	if (ph->d->mealsreached == 1)
	{
		pthread_mutex_unlock(&ph->d->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&ph->d->mutex_death);
	return (0);
}

int	timer(t_philo *philo)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;
	t_philo				*ph;

	ph = philo;
	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < ph->d->nrfilos)
		{
			pthread_mutex_lock(&ph[i].d->mutex_time);
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			if (has_died(&ph[i], current_time) == 1)
			{
				pthread_mutex_unlock(&ph[i].d->mutex_time);
				return (0);
			}
			pthread_mutex_unlock(&ph[i].d->mutex_time);
			i++;
		}
	}
	return (0);
}
